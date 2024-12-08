#include "PermissionManager.h"

namespace app {
    // immediately initialize the singleton instance to ensure only one is created (thread-safety).
    PermissionManager *PermissionManager::instance = new PermissionManager();

    PermissionManager *PermissionManager::getInstance() {
        return instance;
    }

    void PermissionManager::requestRead() {
        const auto thrId = this_thread::get_id();
        // if the thread has already `write` permission, return (as it's stronger than `read` permission)
        if (this->writeLocks.find(thrId) != this->writeLocks.end()) {
            return;
        }
        // if the current thread isn't locking already the mutex
        if (this->readLocks.find(thrId) == this->readLocks.end()) {
            this->readLocks[thrId] = shared_lock(this->mtx);
        }
    }

    void PermissionManager::requestWrite() {
        const auto thrId = this_thread::get_id();
        // if the current thread isn't locking already the mutex
        if (this->writeLocks.find(thrId) == this->writeLocks.end()) {
            this->writeLocks[thrId] = unique_lock(this->mtx);
        }
    }

    void PermissionManager::unlock() {
        const auto thrId = this_thread::get_id();
        // if the current thread is locking the mutex - unlock it by removing it from the corresponding map
        if (this->readLocks.find(thrId) != this->readLocks.end()) {
            this->readLocks.erase(thrId);
        } else if (this->writeLocks.find(thrId) != this->writeLocks.end()) {
            this->writeLocks.erase(thrId);
        }
    }
} // app
