#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

int lru(int pages[], int n, int capacity) {
    list<int> cache;
    unordered_map<int, list<int>::iterator> map;
    int page_faults = 0;

    for (int i = 0; i < n; ++i) {
        if (map.find(pages[i]) != map.end()) {
            cache.erase(map[pages[i]]);
            map.erase(pages[i]);
        } else {
            if (cache.size() == capacity) {
                int least_recently_used = cache.back();
                cache.pop_back();
                map.erase(least_recently_used);
            }
            page_faults++;
        }
        cache.push_front(pages[i]);
        map[pages[i]] = cache.begin();
    }

    return page_faults;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    cout << "Page faults using LRU: " << lru(pages, n, capacity) << endl;

    return 0;
}

