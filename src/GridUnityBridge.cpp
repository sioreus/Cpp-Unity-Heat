#include "GridSimulation.h"
#include <vector>
#include <string>

#if defined(_MSC_VER)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

// Global DLL Variables
static std::vector<float> g_Grid;
static std::vector<float> g_prevGrid;
static std::vector<float> g_nextGrid;
static GridSimulation* g_GridSimulation = nullptr;
static int g_Width = 0;
static int g_Height = 0;

extern "C" {
    EXPORT void InitGrid(int width, int height) {
        if (g_GridSimulation) {
            delete g_GridSimulation;
        }
        g_Grid.resize(width * height, 0.0f);
        g_prevGrid.resize(width * height, 0.0f);
        g_nextGrid.resize(width * height, 0.0f);
        g_Width = width;
        g_Height = height;

        g_GridSimulation = new GridSimulation(g_Grid, g_prevGrid, g_nextGrid, height, width);
    }

    EXPORT void ModifyTile(int x, int y, float du) {
        if (0 <= y && y < g_Height && 0 <= x && x < g_Width) {
            g_Grid[(y * g_Width) + x] += du;
        }
        
    }

    EXPORT int StepHeatNative(float alpha, float dx, float dy, float dt, float* outGrid, int max) {
        
        if (!g_GridSimulation) {
            return 0;
        }

        g_GridSimulation->StepHeat(alpha, dx, dy, dt);

        int full_updated = 0;

        for (int y = 0; y < g_Height; ++y) {
            for (int x = 0; x < g_Width; ++x) {
                outGrid[(y * g_Width) + x] = g_Grid[(y * g_Width) + x];
                full_updated += 1;
            }
        }

        return full_updated;

    }
}