#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
};

void roundRobinScheduling(const vector<Process>& processes, int quantum) {
    queue<Process> readyQueue;
    vector<int> turnaroundTime(processes.size());
    vector<int> waitingTime(processes.size());
    
    int currentTime = 0;
    int totalBurstTime = 0;
    for (const auto& process : processes) {
        totalBurstTime += process.burstTime;
    }

    for (int i = 0; i < processes.size(); ++i) {
        readyQueue.push(processes[i]);
    }

    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int executeTime = min(quantum, currentProcess.remainingTime);
        currentTime += executeTime;
        currentProcess.remainingTime -= executeTime;

        if (currentProcess.remainingTime > 0) {
            readyQueue.push(currentProcess);
        } else {
            turnaroundTime[currentProcess.id] = currentTime;
            waitingTime[currentProcess.id] = currentTime - currentProcess.burstTime;
        }
    }

    cout << "Process\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < processes.size(); ++i) {
        cout << processes[i].id << "\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    double averageTurnaroundTime = 0, averageWaitingTime = 0;
    for (int i = 0; i < processes.size(); ++i) {
        averageTurnaroundTime += turnaroundTime[i];
        averageWaitingTime += waitingTime[i];
    }
    averageTurnaroundTime /= processes.size();
    averageWaitingTime /= processes.size();

    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
}

int main() {
    vector<Process> processes = {
        {0, 10, 10},
        {1, 5, 5},
        {2, 8, 8},
        {3, 12, 12}
    };

    int quantum = 3;

    roundRobinScheduling(processes, quantum);

    return 0;
}

