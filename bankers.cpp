#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_RESOURCES = 3;
const int MAX_PROCESSES = 5;

vector<int> available(MAX_RESOURCES);
vector<vector<int>> maximum(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> allocation(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> need(MAX_PROCESSES, vector<int>(MAX_RESOURCES));

bool isSafe(int process_id, const vector<int>& request) {
    vector<int> work = available;
    vector<bool> finish(MAX_PROCESSES, false);

    // Try to allocate the requested resources temporarily
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    int count = 0;
    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; ++k) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break; // System is in an unsafe state
        }
    }

    // Restore the state of the system
    if (count == MAX_PROCESSES) {
        return true; // Request can be granted
    } else {
        // Request cannot be granted, restore the state of the system
        for (int i = 0; i < MAX_RESOURCES; ++i) {
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return false;
    }
}

bool requestResources(int process_id, const vector<int>& request) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (request[i] > need[process_id][i] || request[i] > available[i]) {
            return false; // Request exceeds maximum demand or available resources
        }
    }

    if (isSafe(process_id, request)) {
        for (int i = 0; i < MAX_RESOURCES; ++i) {
            available[i] -= request[i];
            allocation[process_id][i] += request[i];
            need[process_id][i] -= request[i];
        }
        return true; // Request granted
    } else {
        return false; // Request denied
    }
}

int main() {
    // Initialize available resources
    cout << "Enter available resources:" << endl;
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        cin >> available[i];
    }

    // Initialize maximum resources needed by each process
    cout << "Enter maximum resources needed by each process:" << endl;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            cin >> maximum[i][j];
            need[i][j] = maximum[i][j];
        }
    }

    // Process resource requests
    int process_id;
    vector<int> request(MAX_RESOURCES);
    cout << "Enter process id and requested resources:" << endl;
    cin >> process_id;
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        cin >> request[i];
    }

    if (requestResources(process_id, request)) {
        cout << "Request granted. System is in safe state." << endl;
    } else {
        cout << "Request denied. System is in unsafe state." << endl;
    }

    return 0;
}

