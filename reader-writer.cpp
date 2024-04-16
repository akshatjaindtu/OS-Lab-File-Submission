#include <iostream>
#include <thread>
#include <atomic>
#include <semaphore.h>

using namespace std;

// Constants
const int NUM_READERS = 3;
const int NUM_WRITERS = 2;

// Shared variables
int data = 0;
atomic<int> reader_count(0);
sem_t mutex, rw_mutex;

// Reader function
void reader(int id) {
    while (true) {
        // Entry section
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading
        cout << "Reader " << id << " reads data: " << data << endl;

        // Exit section
        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Simulate reading time
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

// Writer function
void writer(int id) {
    while (true) {
        // Entry section
        sem_wait(&rw_mutex);

        // Writing
        data++;
        cout << "Writer " << id << " writes data: " << data << endl;

        // Exit section
        sem_post(&rw_mutex);

        // Simulate writing time
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    thread readers[NUM_READERS];
    for (int i = 0; i < NUM_READERS; ++i) {
        readers[i] = thread(reader, i);
    }

    // Create writer threads
    thread writers[NUM_WRITERS];
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers[i] = thread(writer, i);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        readers[i].join();
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers[i].join();
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

