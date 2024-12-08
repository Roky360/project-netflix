#include "PermissionManager.h"

#define DISABLE_THREAD_SAFE

namespace app {
#ifdef DISABLE_THREAD_SAFE
    PermissionManager *PermissionManager::instance = new PermissionManager();

    PermissionManager *PermissionManager::getInstance() {
        return instance;
    }

    void PermissionManager::requestRead() {
    }

    void PermissionManager::requestWrite() {
    }

    void PermissionManager::unlock() {
    }
#else
    // immediately initialize the singleton instance to ensure only one is created (thread-safety).
    PermissionManager *PermissionManager::instance = new PermissionManager();

    PermissionManager *PermissionManager::getInstance() {
        return instance;
    }

    void PermissionManager::requestRead() {
        auto thrId = this_thread::get_id();
        // if the current thread isn't locking already the mutex
        if (this->readLocks.find(thrId) == this->readLocks.end()) {
            this->readLocks[thrId] = shared_lock(this->mtx);
        }
    }

    void PermissionManager::requestWrite() {
        auto thrId = this_thread::get_id();
        // if the current thread isn't locking already the mutex
        if (this->writeLocks.find(thrId) == this->writeLocks.end()) {
            this->writeLocks[thrId] = unique_lock(this->mtx);
        }
    }

    void PermissionManager::unlock() {
        auto thrId = this_thread::get_id();
        // if the current thread is locking the mutex - unlock it by removing it from the corresponding map
        if (this->readLocks.find(thrId) != this->readLocks.end()) {
            this->readLocks.erase(thrId);
        } else if (this->writeLocks.find(thrId) != this->writeLocks.end()) {
            this->writeLocks.erase(thrId);
        }
    }
#endif
} // app
