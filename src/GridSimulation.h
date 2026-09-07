#pragma once
#include <vector>
#include <string>

class GridSimulation {
public:
    GridSimulation(std::vector<float>& grid);

private:
    std::vector<float>& _grid;
    void StepHeat(float alpha, float dx, float dt);

}