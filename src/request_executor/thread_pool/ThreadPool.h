//
// Created by avi on 12/29/2024.
//

#ifndef NAKNIKI_NETFLIX_THREADPOOL_H
#define NAKNIKI_NETFLIX_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
using namespace std;

class ThreadPool {
public:
    /**
     * Constructor
     * @param num_threads the amount of threads in the threadpool
     */
    ThreadPool(size_t num_threads);

    /**
     * Deletes the thread pool and all of its threads
     */
    ~ThreadPool();

    /**
     * Adds a task to the tasks queue
     * @param task function
     */
    void enqueueTask(const std::function<void()>& task);
private:
    // Vector to store worker threads
    vector<thread> threads;

    // Queue of tasks
    queue<function<void()> > tasks;

    // Mutex to manage access to shared data
    mutex queueMutex;

    // Condition variable to signal changes in the state of
    // the tasks queue
    condition_variable conditionVariable;

    // Flag to indicate whether the thread pool should stop
    // or not
    bool stop = false;

    // Controls the thread distribution
    void workerThread();
};


#endif //NAKNIKI_NETFLIX_THREADPOOL_H
