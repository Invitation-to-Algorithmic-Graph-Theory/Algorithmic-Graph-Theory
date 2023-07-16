#include <bits/stdc++.h>

using namespace std;

// Function to calculate the heuristic value
int calculateHeuristic(const string& state, const string& target) {
    int heuristic = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != target[i])
            heuristic++;
    }
    return heuristic;
}

// Function to perform a group operation on the state
void performGroupOperation(string& state, const vector<vector<int>>& operation) {
    for (size_t i = 0; i < state.size(); ++i) {
        int element = state[i] - '0';
        state[i] = operation[element][0] + '0';
    }
}

// Function to solve the Merlin's Magic puzzle using A* search
bool solveMerlinsMagicPuzzle(const string& initial, const string& target,
                             const vector<vector<vector<int>>>& operations) {
    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);

    unordered_map<string, int> gScore;
    unordered_map<string, string> cameFrom;
    unordered_map<string, bool> visited;

    pq.push({initial, 0});
    gScore[initial] = 0;

    while (!pq.empty()) {
        string current = pq.top().first;
        pq.pop();

        if (current == target)
            return true;

        visited[current] = true;

        for (const auto& operation : operations) {
            string next = current;
            performGroupOperation(next, operation);

            int tentativeGScore = gScore[current] + 1;

            if (!visited[next] || tentativeGScore < gScore[next]) {
                cameFrom[next] = current;
                gScore[next] = tentativeGScore;
                int fScore = tentativeGScore + calculateHeuristic(next, target);
                pq.push({next, fScore});
            }
        }
    }

    return false;
}

// Function to reconstruct the path from the initial state to the target state
vector<string> reconstructPath(const string& initial, const string& target,
                               const unordered_map<string, string>& cameFrom) {
    vector<string> path;
    string current = target;
    while (current != initial) {
        path.push_back(current);
        current = cameFrom.at(current);
    }
    path.push_back(initial);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    string initial = "012102201";
    string target = "000000000";

    vector<vector<vector<int>>> operations = {
        {{0, 1, 2}, {1, 2, 0}, {2, 0, 1}},
        {{1, 0, 2}, {0, 2, 1}, {2, 1, 0}},
        {{2, 1, 0}, {1, 0, 2}, {0, 2, 1}}
    };

    if (solveMerlinsMagicPuzzle(initial, target, operations)) {
        cout << "Merlin's Magic puzzle solved!" << endl;

        unordered_map<string, string> cameFrom;
        vector<string> path = reconstructPath(initial, target, cameFrom);

        cout << "Path: ";
        for (const string& state : path) {
            cout << state << " -> ";
        }
        cout << "Goal" << endl;
    } else {
        cout << "No solution found for the Merlin's Magic puzzle." << endl;
    }

    return 0;
}
