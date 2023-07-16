 #include <bits/stdc++.h>

using namespace std;

// Function to toggle the state of a light
void toggleLight(int& light) {
    light = (light == 0) ? 1 : 0;
}

// Function to toggle the lights in a given row and column
void toggleLights(vector<vector<int>>& grid, int row, int col) {
    toggleLight(grid[row][col]);
    if (row > 0)
        toggleLight(grid[row - 1][col]);
    if (row < 2)
        toggleLight(grid[row + 1][col]);
    if (col > 0)
        toggleLight(grid[row][col - 1]);
    if (col < 2)
        toggleLight(grid[row][col + 1]);
}

// Function to check if all lights are turned off
bool allLightsOff(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int light : row) {
            if (light != 0)
                return false;
        }
    }
    return true;
}

// Function to solve the Lights Out puzzle using BFS
bool solveLightsOutPuzzle(vector<vector<int>>& grid) {
    queue<vector<vector<int>>> q;
    unordered_set<string> visited;

    q.push(grid);
    visited.insert(serializeGrid(grid));

    while (!q.empty()) {
        vector<vector<int>> currGrid = q.front();
        q.pop();

        if (allLightsOff(currGrid))
            return true;

        // Generate neighboring states by toggling lights
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                vector<vector<int>> nextGrid = currGrid;
                toggleLights(nextGrid, row, col);

                string serializedGrid = serializeGrid(nextGrid);
                if (visited.find(serializedGrid) == visited.end()) {
                    q.push(nextGrid);
                    visited.insert(serializedGrid);
                }
            }
        }
    }

    return false;
}

// Function to serialize the grid into a string
string serializeGrid(const vector<vector<int>>& grid) {
    string serializedGrid;
    for (const auto& row : grid) {
        for (int light : row) {
            serializedGrid += to_string(light);
        }
    }
    return serializedGrid;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 0}
    };

    if (solveLightsOutPuzzle(grid)) {
        cout << "Lights Out puzzle solved!" << endl;
    } else {
        cout << "No solution found for the Lights Out puzzle." << endl;
    }

    return 0;
}
