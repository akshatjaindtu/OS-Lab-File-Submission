#include <iostream>
#include <thread>
#include <atomic>
#include <semaphore.h>

using namespace std;

#define NUM_THREADS 2

atomic<bool> wants_to_enter[NUM_THREADS] = {false, false};
atomic<int> turn = 0;

sem_t semaphore;

void dekker(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        wants_to_enter[thread_id] = true;
        while (wants_to_enter[1 - thread_id]) {
            if (turn != thread_id) {
                wants_to_enter[thread_id] = false;
                while (turn != thread_id) {}
                wants_to_enter[thread_id] = true;
            }
        }

        cout << "Thread " << thread_id << " is in critical section" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        turn = 1 - thread_id;
        wants_to_enter[thread_id] = false;
    }
}

int main() {
    sem_init(&semaphore, 0, 1);

    thread t1(dekker, 0);
    thread t2(dekker, 1);

    t1.join();
    t2.join();

    sem_destroy(&semaphore);

    return 0;
}

