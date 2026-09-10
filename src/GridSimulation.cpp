#include <vector>
#include <string>
#include "GridSimulation.h"

GridSimulation::GridSimulation(std::vector<float>& grid, std::vector<float>& prevGrid, std::vector<float>& nextGrid,
                            int rows, int cols) : _grid(grid), _prevGrid(prevGrid), _nextGrid(nextGrid), 
                            _gridRows(rows), _gridCols(cols) {

}




float GridSimulation::CalculateNeighbors(int x, int y, float dx, float dy) {
    float u_xx = 0.0f;
    float u_yy = 0.0f;
    // u_xx = (u(x+dx) - 2u(x) + u(x-dx)) / (dx)^2
    
    // Forward Difference if Left/Top Boundary
    // Backward Difference if Right/Bottom Boundary 
    // We need to have neumman insulated boundary ocnditions for the outer edges no heat enter or leave the boundaries
    // if on the edge du/dx = 0, in order to satisfy this we reflect the inside neighbor
    // Central Difference if Middle
    if (x == 0) {
        u_xx = (_grid[(y * _gridCols) + (x + 1)] - (2 * _grid[(y * _gridCols) + x]) + _grid[(y * _gridCols) + (x + 1)]); 
    }
    else if (x == _gridCols - 1) {
        u_xx = (_grid[(y * _gridCols) + (x - 1)] - (2 * _grid[(y * _gridCols) + x]) + _grid[(y * _gridCols) + (x - 1)]);
    }
    else {
        u_xx = (_grid[(y * _gridCols) + (x - 1)] - (2 * _grid[(y * _gridCols) + x]) + _grid[(y * _gridCols) + (x + 1)]);
    }
    

    if (y == 0) {
        u_yy = (_grid[((y + 1) * _gridCols) + x] - (2 * _grid[(y * _gridCols) + x]) + _grid[((y + 1) * _gridCols) + x]);
    }
    else if (y == _gridRows - 1) {
        u_yy = (_grid[((y - 1) * _gridCols) + x] - (2 * _grid[(y * _gridCols) + x]) + _grid[((y - 1) * _gridCols) + x]);
    }
    else {
        u_yy = (_grid[((y - 1) * _gridCols) + x] - (2 * _grid[(y * _gridCols) + x]) + _grid[((y + 1) * _gridCols) + x]);
    }

    u_xx /= (dx * dx);
    u_yy /= (dy * dy);
    
    return (u_xx + u_yy);
    
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
            _nextGrid[(y * _gridCols) + x] = _grid[(y * _gridCols) + x] + (dt * alpha * CalculateNeighbors(x, y, dx, dy));
        }
    }
    _prevGrid = _grid;
    _grid = _nextGrid;
}