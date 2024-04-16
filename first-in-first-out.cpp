#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int fifo(int pages[], int n, int capacity) {
    queue<int> q;
    unordered_set<int> s;
    int page_faults = 0;

    for (int i = 0; i < n; ++i) {
        if (s.size() < capacity) {
            if (s.find(pages[i]) == s.end()) {
                s.insert(pages[i]);
                q.push(pages[i]);
                page_faults++;
            }
        } else {
            if (s.find(pages[i]) == s.end()) {
                int front = q.front();
                q.pop();
                s.erase(front);
                s.insert(pages[i]);
                q.push(pages[i]);
                page_faults++;
            }
        }
    }

    return page_faults;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    cout << "Page faults using FIFO: " << fifo(pages, n, capacity) << endl;

    return 0;
}

