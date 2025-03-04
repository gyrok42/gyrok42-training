// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file dispatcher.h
 * @brief Dispatcher Implementation
 *
 * This scheduler is designed to execute functions only once at their scheduled
 * time with a precision of 1 millisecond.
 *
 */
#pragma once
#include <memory>
#include <thread>
#include <vector>

namespace scheduler {
/**
 * @class Dispatcher
 * @brief Manages execution of scheduled tasks in separate threads.
 */
template <typename SCHEDULER>
class Dispatcher {
 public:
  /**
   * @brief Launches a scheduler in a separate thread.
   * @param scheduler Reference to the scheduler managing tasks.
   * @return true if success, otherwise false.
   * If it has already been launched but not stopped,
   * the launch will not re-launch. It will return false.
   */
  bool launch(std::weak_ptr<SCHEDULER> scheduler) {
    if (_tasksRunner != nullptr) {
      return false;
    }
    _tasksRunner = std::make_unique<std::thread>(
        &Dispatcher::runTasksAsScheduled, this, scheduler);
    return true;
  }

  /**
   * @brief Spawns and executes all scheduled tasks that are ready at the given
   * time.
   *
   * This function retrieves all functions that are ready to execute at
   * `timeNow` from the scheduler and spawns each one in a separate detached
   * thread.
   *
   * @tparam SCHEDULER The scheduler type that manages the scheduled functions.
   * @param timeNow The current absolute time (`std::time_t`) to check for ready
   * tasks.
   * @param scheduler A weak pointer to the scheduler instance, allowing safe
   * access.
   *
   * @return true: Ok, false: error with scheduler, stop.
   *
   * @note Each ready function is executed in a separate detached thread.
   */
  bool spawnReady(time_t timeNow, std::weak_ptr<SCHEDULER> scheduler) {
    auto schedulerPtr = scheduler.lock();
    if (schedulerPtr == nullptr) {
      return false;
    }
    auto functions = schedulerPtr->popReady(timeNow);
    for (auto func : functions) {
      std::thread newThread{func};
      newThread.detach();
    }
    return true;
  }

  /**
   * @brief Executes scheduled tasks as per the scheduler's queue.
   * @param scheduler Reference to the scheduler managing tasks.
   */
  void runTasksAsScheduled(std::weak_ptr<SCHEDULER> scheduler) {
    using std::chrono::system_clock;
    using namespace std::chrono_literals;
    for (;;) {
      time_t timeNow = system_clock::to_time_t(system_clock::now());
      if (!spawnReady(timeNow, scheduler) || _stopFlag.load()) {
        break;
      }
      std::this_thread::sleep_for(1ms);
    }
  }

  void stop() {
    _stopFlag.store(true);

    if (_tasksRunner != nullptr) {
      _tasksRunner->join();
    }
  }

 private:
  std::unique_ptr<std::thread> _tasksRunner;
  std::atomic<bool> _stopFlag{false};
  std::vector<std::thread> _threads;
};
}  // namespace scheduler
