#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int startTime;
    int finishTime;
};

bool comparePriority(const Process& p1, const Process& p2) {
    return p1.priority < p2.priority;
}

void priorityScheduling(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), comparePriority);

    int currentTime = 0;
    for (int i = 0; i < processes.size(); ++i) {
        processes[i].startTime = currentTime;
        currentTime += processes[i].burstTime;
        processes[i].finishTime = currentTime;
    }

    cout << "Process\tStart Time\tFinish Time\n";
    for (int i = 0; i < processes.size(); ++i) {
        cout << processes[i].id << "\t" << processes[i].startTime << "\t\t" << processes[i].finishTime << endl;
    }

    double totalTurnaroundTime = 0;
    for (const auto& process : processes) {
        totalTurnaroundTime += process.finishTime - process.startTime;
    }
    double averageTurnaroundTime = totalTurnaroundTime / processes.size();

    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    vector<Process> processes = {
        {0, 10, 3},
        {1, 5, 1},
        {2, 8, 2},
        {3, 12, 4}
    };

    priorityScheduling(processes);

    return 0;
}

