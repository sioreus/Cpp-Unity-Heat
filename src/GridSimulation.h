#pragma once
#include <vector>
#include <string>

class GridSimulation {
public:
    GridSimulation(std::vector<float>& grid, int rows, int cols);

private:
    std::vector<float>& _grid;
    int _gridRows, _gridCols;
    void StepHeat(float alpha, float dx, float dt);

};