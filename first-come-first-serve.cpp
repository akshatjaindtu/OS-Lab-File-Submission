#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

void fcfs(vector<Process>& processes) {
    int currentTime = 0;
    int totalWaitingTime = 0;

    cout << "Time\tProcess\tWaiting Time\n";

    for (const auto& process : processes) {
        if (process.arrivalTime > currentTime) {
            currentTime = process.arrivalTime;
        }

        int waitingTime = currentTime - process.arrivalTime;
        totalWaitingTime += waitingTime;

        cout << currentTime << "\tP" << process.id << "\t" << waitingTime << endl;

        currentTime += process.burstTime;
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 3, 3}
    };

    fcfs(processes);

    return 0;
}

