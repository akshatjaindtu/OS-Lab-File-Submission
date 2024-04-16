#include <iostream>
#include <unordered_set>

using namespace std;

int opt(int pages[], int n, int capacity) {
    unordered_set<int> s;
    int page_faults = 0;

    for (int i = 0; i < n; ++i) {
        if (s.size() < capacity) {
            s.insert(pages[i]);
            page_faults++;
        } else {
            if (s.find(pages[i]) == s.end()) {
                int farthest = i;
                int val = -1;
                for (auto it = s.begin(); it != s.end(); ++it) {
                    int j;
                    for (j = i + 1; j < n; ++j) {
                        if (*it == pages[j]) {
                            if (j > farthest) {
                                farthest = j;
                                val = *it;
                            }
                            break;
                        }
                    }
                    if (j == n) {
                        val = *it;
                        break;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
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

    cout << "Page faults using OPT: " << opt(pages, n, capacity) << endl;

    return 0;
}

