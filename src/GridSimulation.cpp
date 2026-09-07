#include <vector>
#include <string>
#include "GridSimulation.h"

GridSimulation::GridSimulation(std::vector<float>& grid, int rows, int cols) : _grid(grid), _gridRows(rows), _gridCols(cols) {

}


float GridSimulation::CalculateNeighbors(int x, int y, std::string variant = "heat") {
    // u_xx = (u(x+dx) - 2u(x) - u(x-dx)) / (dx)^2
    if (variant == "heat") {
        float x_component = _grid
    }
}


// the Heat Equation is given by du/dt = alpha * (u_xx + u_yy)
void GridSimulation::StepHeat(float alpha, float dx, float dy, float dt) {
    // Apprxoimately du/dt = (u(t+dt) - u(t))/dt
    // Plug this into our heat equation
    // (u(t + dt) - u(t)) / dt = alpha * (u_xx + u_yy)
    // u(t + dt) = u(t) + (dt * alpha * (u_xx + u_yy))
    
    // Grid is flattened for memory efficiency if grid is M x N, _grid[y][x] = _grid[(y * M) + x]
    for (int y = 0; y < _gridRows; ++y) {
        for (int x = 0; x < _gridCols; ++x) {
            _grid[(y * gridRows) + x] 
        }
    }
}