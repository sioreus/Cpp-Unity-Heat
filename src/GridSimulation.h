#pragma once
#include <vector>
#include <string>

class GridSimulation {
public:
    GridSimulation(std::vector<float>* grid, std::vector<float>* prevGrid, std::vector<float>* nextGrid, int rows, int cols);
    void StepHeat(float alpha, float dx, float dy, float dt);
private:
    std::vector<float>& _grid;
    std::vector<float>& _prevGrid;
    std::vector<float>& _nextGrid;
    int _gridRows, _gridCols;
    float CalculateNeighbors(int x, int y, float dx, float dy);
    

};