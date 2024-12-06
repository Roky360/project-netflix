#ifndef PERMISSIONMANAGER_H
#define PERMISSIONMANAGER_H

#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

using namespace std;

namespace app {
    /**
     * Manages a mutex that can be used to multiple read operations (with requestRead) or one write operation
     * (with requestWrite), for thread-safety support for shared resources.
     *
     * Automatically tracks the locks that each thread owns.
     */
    class PermissionManager {
        static PermissionManager *instance;
        shared_mutex mtx; // Shared mutex of the threads that uses this class
        unordered_map<thread::id, shared_lock<shared_mutex> > readLocks{};
        unordered_map<thread::id, unique_lock<shared_mutex> > writeLocks{};

        PermissionManager() = default;

    public:
        ~PermissionManager() = default;

        static PermissionManager *getInstance();

        // Delete copy constructor and assignment operator to ensure a single instance
        PermissionManager(const PermissionManager &) = delete;

        PermissionManager &operator=(const PermissionManager &) = delete;

        /**
         * Request a read permission. Blocks until mutex is available.
         */
        void requestRead();

        /**
         * Request a write permission. Blocks until mutex is available.
         */
        void requestWrite();

        /**
         * Releases the mutex lock for the thread holding it.
         */
        void unlock();
    };
} // app

#endif //PERMISSIONMANAGER_H
