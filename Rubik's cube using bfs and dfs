#include <bits/stdc++.h>

using namespace std;

// Define the Rubik's Cube class
class RubiksCube {
private:
    string cubeState; // Stores the current state of the cube
    unordered_map<char, vector<char>> moves; // Stores the possible moves for each face

public:
    RubiksCube(string initialState) {
        cubeState = initialState;
        initializeMoves();
    }

    // Initialize the possible moves for each face
    void initializeMoves() {
        moves['U'] = {'F', 'R', 'B', 'L'};
        moves['D'] = {'F', 'L', 'B', 'R'};
        moves['F'] = {'U', 'L', 'D', 'R'};
        moves['B'] = {'U', 'R', 'D', 'L'};
        moves['L'] = {'U', 'F', 'D', 'B'};
        moves['R'] = {'U', 'B', 'D', 'F'};
    }

    // Apply a move to the cube state
    void applyMove(char face) {
        string newState = cubeState;
        vector<char> affectedFaces = moves[face];

        for (char& affectedFace : affectedFaces) {
            string faceState = getFaceState(affectedFace);
            rotate(faceState.begin(), faceState.begin() + 6, faceState.end());
            setFaceState(affectedFace, faceState);
        }

        setFaceState(face, newState);
    }

    // Get the state of a face
    string getFaceState(char face) {
        int startIndex = cubeState.find(face);
        return cubeState.substr(startIndex + 1, 9);
    }

    // Set the state of a face
    void setFaceState(char face, string newState) {
        int startIndex = cubeState.find(face);
        cubeState.replace(startIndex + 1, 9, newState);
    }

    // Check if the cube is solved
    bool isSolved() {
        for (char face = 'U'; face <= 'B'; face++) {
            string faceState = getFaceState(face);
            char color = faceState[0];
            if (count(faceState.begin(), faceState.end(), color) != 9) {
                return false;
            }
        }
        return true;
    }
};

// Breadth-First Search (BFS) algorithm
string BFSSearch(RubiksCube& cube) {
    queue<pair<string, string>> q;
    unordered_map<string, bool> visited;
    string initialState = cube.getFaceState('U') + cube.getFaceState('D') + cube.getFaceState('F') +
                          cube.getFaceState('B') + cube.getFaceState('L') + cube.getFaceState('R');
    q.push({initialState, ""});
    visited[initialState] = true;

    while (!q.empty()) {
        string currentState = q.front().first;
        string currentPath = q.front().second;
        q.pop();

        RubiksCube currentCube(currentState);

        if (currentCube.isSolved()) {
            return currentPath;
        }

        for (char face = 'U'; face <= 'B'; face++) {
            RubiksCube newCube = currentCube;
            newCube.applyMove(face);
            string newState = newCube.getFaceState('U') + newCube.getFaceState('D') + newCube.getFaceState('F') +
                              newCube.getFaceState('B') + newCube.getFaceState('L') + newCube.getFaceState('R');
            if (!visited[newState]) {
                q.push({newState, currentPath + face});
                visited[newState] = true;
            }
        }
    }

    return "No solution found.";
}

// Depth-First Search (DFS) algorithm
string DFSSearch(RubiksCube& cube, int maxDepth, string currentPath = "") {
    if (maxDepth == 0) {
        return "";
    }

    if (cube.isSolved()) {
        return currentPath;
    }

    for (char face = 'U'; face <= 'B'; face++) {
        RubiksCube newCube = cube;
        newCube.applyMove(face);
        string result = DFSSearch(newCube, maxDepth - 1, currentPath + face);
        if (result != "No solution found.") {
            return result;
        }
    }

    return "No solution found.";
}

int main() {
    string initialState = "UWWUWWUWWUOOOYYYGGGBBBRRR";
    
    RubiksCube cube(initialState);

    // Solve using BFS
    string bfsSolution = BFSSearch(cube);
    cout << "BFS Solution: " << bfsSolution << endl;

    // Solve using DFS with a maximum depth of 10
    string dfsSolution = DFSSearch(cube, 10);
    cout << "DFS Solution: " << dfsSolution << endl;

    return 0;
}
