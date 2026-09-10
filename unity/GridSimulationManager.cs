using UnityEngine;
using UnityEngine.InputSystem;
using System.Runtime.InteropServices;

public class GridSimulationManager : MonoBehaviour
{
    const string DLLName = "GridSimulation";

    [DllImport(DLLName)]
    private static extern void InitGrid(int width, int height);

    [DllImport(DLLName)]
    private static extern void ModifyTile(int x, int y, float du);

    [DllImport(DLLName)]
    private static extern int StepHeatNative(float alpha, float dx, float dy, float dt, float[] outGrid, int max);

    private GameObject[] tileGridObjects;
    private float[] gridDataBuffer;
    private int gridWidth = 30;
    private int gridHeight = 30;
    [SerializeField] float alpha = 1.0f;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Debug.Log("Testing C++ Dll connection");


        InitGrid(gridWidth, gridHeight);
        tileGridObjects = new GameObject[gridWidth * gridHeight];
        gridDataBuffer = new float[gridWidth * gridHeight];
        for (int y = 0; y < gridHeight; y++)
        {
            for (int x = 0; x < gridWidth; x++)
            {
                GameObject tile = GameObject.CreatePrimitive(PrimitiveType.Cube);
                tile.transform.position = new Vector3(x, 0, y);
                tile.transform.localScale = new Vector3(0.9f, 0.1f, 0.9f);
                tileGridObjects[(y * gridWidth) + x] = tile;
                gridDataBuffer[(y * gridWidth) + x] = 0.0f;

            }
        }
        ModifyTile(6, 6, 5.0f);

    }

    void UpdateVisuals()
    {
        float totalheat = 0.0f;
        for (int i = 0; i < tileGridObjects.Length; i++)
        {
            float heatValue = gridDataBuffer[i];
            if (float.IsNaN(heatValue) || float.IsInfinity(heatValue))
            {
                Debug.Log("Simulation exploded");
                break;
            }
            totalheat += gridDataBuffer[i];
            //Debug.Log(heatValue);
            // Clamps so heat value between 0 and 1
            float t = Mathf.Clamp01(heatValue/ 100.0f);

            // Linear interpolation
            Color tileColor = Color.Lerp(Color.cyan, Color.red, t);
            Renderer rend = tileGridObjects[i].GetComponent<Renderer>();
            rend.material.color = tileColor;
        }
        Debug.Log("Total Heat: " + totalheat);
    }

    // Update is called once per frame
    void FixedUpdate()
    {

        float safeDt = Mathf.Min(Time.deltaTime, 0.05f);
        StepHeatNative(alpha, 1.0f, 1.0f, safeDt, gridDataBuffer, gridWidth * gridHeight);

        if (Mouse.current != null &&  Mouse.current.leftButton.isPressed)
        {
            Vector2 mousePos = Mouse.current.position.ReadValue();
            Ray ray = Camera.main.ScreenPointToRay(mousePos);
            if (Physics.Raycast(ray, out RaycastHit hit))
            {
                int x = Mathf.RoundToInt(hit.transform.position.x);
                int y = Mathf.RoundToInt(hit.transform.position.z);

                if (0 <= x && x < gridWidth && 0 <= y && y < gridHeight)
                {
                    ModifyTile(x, y, 30.0f);
                }
            }
        }
        UpdateVisuals();
    }
}
