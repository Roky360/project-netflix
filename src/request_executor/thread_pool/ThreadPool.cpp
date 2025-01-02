#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t threadCount) : stop(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&ThreadPool::workerRoutine, this);
    }
}

ThreadPool::~ThreadPool() {
    // Makes sure that nothing messes with setting the condition to true
    unique_lock lock(queueMutex);
    stop = true;
    lock.unlock();
    // Lets all threads know to stop work
    conditionVariable.notify_all();
    // Returns all threads to main
    for (thread &worker: threads) {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::enqueueTask(const std::function<void()> &task) {
    { // make the lock auto-unlock when exiting the block
        lock_guard lock(queueMutex);
        tasks.push(task);
    }
    conditionVariable.notify_one();
}

void ThreadPool::workerRoutine() {
    // Runs until told to stop AND there are no tasks left
    while (true) {
        function<void()> task;
        { // make the lock auto-unlock when exiting the block
            // Makes sure that only a single thread executes the task
            unique_lock lock(queueMutex);
            conditionVariable.wait(lock, [this] { return stop || !tasks.empty(); });
            // In case told to stop and no tasks are left, stops the infinite loop
            if (stop && tasks.empty())
                return;
            // Extract the first task from the queue and execute it
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
