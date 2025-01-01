//
// Created by avi on 12/29/2024.
//

#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t threadCount) : stop(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&ThreadPool::workerThread, this);
    }
}

ThreadPool::~ThreadPool() {
    // Makes sure that nothing messes with setting the condition to true
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
    lock.unlock();
    // Lets all threads know to stop work
    conditionVariable.notify_all();
    // Returns all threads to main
    for (std::thread& worker : threads) {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::enqueueTask(const std::function<void()>& task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(task);
    }
    conditionVariable.notify_one();
}

void ThreadPool::workerThread() {
    // Runs until told to stop AND there are no tasks left
    while (true) {
        std::function<void()> task;
        {
            // Makes sure that only a single thread executes the task
            std::unique_lock<std::mutex> lock(queueMutex);
            conditionVariable.wait(lock, [this] { return stop || !tasks.empty(); });
            // In case told to stop and no tasks are left, stops the infinite loop
            if (stop && tasks.empty())
                return;
            // Moves the queue one step forward
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}


