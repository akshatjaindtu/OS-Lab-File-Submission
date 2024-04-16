#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareBurstTime(const Process& p1, const Process& p2) {
    return p1.burstTime < p2.burstTime;
}

void sjfNonPreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int totalWaitingTime = 0;

    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\n";

    for (int i = 0; i < processes.size(); ++i) {
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].arrivalTime = currentTime;
        currentTime += processes[i].burstTime;
        int waitingTime = processes[i].arrivalTime - processes[i].burstTime;
        totalWaitingTime += waitingTime;
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << waitingTime << endl;
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

    sjfNonPreemptive(processes);

    return 0;
}

