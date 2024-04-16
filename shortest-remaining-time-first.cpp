#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareRemainingTime(const Process& p1, const Process& p2) {
    return p1.remainingTime < p2.remainingTime;
}

void srtf(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int totalWaitingTime = 0;
    int completedProcesses = 0;

    cout << "Time\tProcess\n";

    while (completedProcesses < processes.size()) {
        int shortestIndex = -1;
        int shortestRemainingTime = INT_MAX;

        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestRemainingTime && processes[i].remainingTime > 0) {
                shortestIndex = i;
                shortestRemainingTime = processes[i].remainingTime;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        cout << currentTime << "\tP" << processes[shortestIndex].id << endl;
        processes[shortestIndex].remainingTime--;
        currentTime++;

        if (processes[shortestIndex].remainingTime == 0) {
            int waitingTime = currentTime - processes[shortestIndex].arrivalTime - processes[shortestIndex].burstTime;
            totalWaitingTime += waitingTime;
            completedProcesses++;
        }
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 6, 6},
        {2, 1, 8, 8},
        {3, 2, 7, 7},
        {4, 3, 3, 3}
    };

    srtf(processes);

    return 0;
}

