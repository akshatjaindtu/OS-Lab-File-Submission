#include <iostream>
#include <thread>
#include <atomic>
#include <semaphore.h>

using namespace std;

#define NUM_THREADS 2

// Flags to indicate if a thread wants to enter the critical section
atomic<bool> wants_to_enter[NUM_THREADS] = {false, false};

// Indicates whose turn is it to enter the critical section
atomic<int> turn = 0;

// Semaphore to ensure mutual exclusion
sem_t semaphore;

void dekker(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        // Entry section
        wants_to_enter[thread_id] = true;
        while (wants_to_enter[1 - thread_id]) {
            if (turn != thread_id) {
                wants_to_enter[thread_id] = false;
                while (turn != thread_id) {}
                wants_to_enter[thread_id] = true;
            }
        }

        // Critical section
        cout << "Thread " << thread_id << " is in critical section" << endl;
        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(500));

        // Exit section
        turn = 1 - thread_id;
        wants_to_enter[thread_id] = false;
    }
}

int main() {
    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Create threads
    thread t1(dekker, 0);
    thread t2(dekker, 1);

    // Join threads
    t1.join();
    t2.join();

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}

