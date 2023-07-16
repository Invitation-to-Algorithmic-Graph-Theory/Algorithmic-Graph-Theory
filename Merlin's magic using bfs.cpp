#include <bits/stdc++.h>
using namespace std;

// Function to perform a group operation on the grid
void performGroupOperation(vector<vector<int>>& grid, const vector<vector<int>>& operation) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int element = grid[row][col];
            grid[row][col] = operation[element][0];
        }
    }
}

// Function to check if the grid matches the target configuration
bool isTargetConfiguration(const vector<vector<int>>& grid, const vector<vector<int>>& target) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (grid[row][col] != target[row][col])
                return false;
        }
    }
    return true;
}

// Function to solve the Merlin's Magic puzzle using BFS
bool solveMerlinsMagicPuzzle(vector<vector<int>>& grid, const vector<vector<int>>& target,
                            const vector<vector<vector<int>>>& operations) {
    queue<vector<vector<int>>> q;
    unordered_set<string> visited;

    q.push(grid);
    visited.insert(serializeGrid(grid));

    while (!q.empty()) {
        vector<vector<int>> currGrid = q.front();
        q.pop();

        if (isTargetConfiguration(currGrid, target))
            return true;

        // Generate neighboring states by performing group operations
        for (const auto& operation : operations) {
            vector<vector<int>> nextGrid = currGrid;
            performGroupOperation(nextGrid, operation);

            string serializedGrid = serializeGrid(nextGrid);
            if (visited.find(serializedGrid) == visited.end()) {
                q.push(nextGrid);
                visited.insert(serializedGrid);
            }
        }
    }

    return false;
}

// Function to serialize the grid into a string
string serializeGrid(const vector<vector<int>>& grid) {
    string serializedGrid;
    for (const auto& row : grid) {
        for (int element : row) {
            serializedGrid += to_string(element);
        }
    }
    return serializedGrid;
}

int main() {
    vector<vector<int>> grid = {
        {0, 1, 2},
        {1, 2, 0},
        {2, 0, 1}
    };

    vector<vector<int>> target = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    vector<vector<vector<int>>> operations = {
        {{0, 1, 2}, {1, 2, 0}, {2, 0, 1}},
        {{1, 0, 2}, {0, 2, 1}, {2, 1, 0}},
        {{2, 1, 0}, {1, 0, 2}, {0, 2, 1}}
    };

    if (solveMerlinsMagicPuzzle(grid, target, operations)) {
        cout << "Merlin's Magic puzzle solved!" << endl;
    } else {
        cout << "No solution found for the Merlin's Magic puzzle." << endl;
    }

    return 0;
}
