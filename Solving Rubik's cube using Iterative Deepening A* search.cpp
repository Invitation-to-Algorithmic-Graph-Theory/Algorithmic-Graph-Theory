#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

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

// IDA* search algorithm
bool IDAStarSearch(RubiksCube& cube, string& solution, int depth, int maxDepth) {
    if (cube.isSolved()) {
        return true;
    }

    if (depth + heuristic(cube) > maxDepth) {
        return false;
    }

    for (char face = 'U'; face <= 'B'; face++) {
        cube.applyMove(face);
        solution.push_back(face);

        if (IDAStarSearch(cube, solution, depth + 1, maxDepth)) {
            return true;
        }

        cube.applyMove(oppositeMove(face));
        solution.pop_back();
    }

    return false;
}

// Heuristic function for estimating the number of moves to solve the cube
int heuristic(RubiksCube& cube) {
    int count = 0;
    for (char face = 'U'; face <= 'B'; face++) {
        string faceState = cube.getFaceState(face);
        char color = faceState[0];
        count += 9 - count(faceState.begin(), faceState.end(), color);
    }
    return count / 4;
}

// Get the opposite move of a given move
char oppositeMove(char move) {
    switch (move) {
        case 'U': return 'D';
        case 'D': return 'U';
        case 'F': return 'B';
        case 'B': return 'F';
        case 'L': return 'R';
        case 'R': return 'L';
    }
    return ' ';
}

// Solve the Rubik's Cube using IDA* algorithm
string solveRubiksCube(string initialState) {
    RubiksCube cube(initialState);
    string solution;

    for (int maxDepth = 0; maxDepth < 20; maxDepth++) {
        if (IDAStarSearch(cube, solution, 0, maxDepth)) {
            return solution;
        }
    }

    return "No solution found.";
}

int main() {
    string initialState = "UWWUWWUWWUOOOYYYGGGBBBRRR";
    string solution = solveRubiksCube(initialState);

    cout << "Solution: " << solution << endl;

    return 0;
}
