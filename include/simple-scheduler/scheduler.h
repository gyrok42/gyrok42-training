// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file scheduler.h
 * @brief Function Scheduler Implementation
 *
 * This scheduler is designed to execute functions only once at their scheduled
 * time with a precision of 1 millisecond.
 *
 */
#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

namespace scheduler {
using ScheduledFunction = std::function<void()>;
/**
 * @class Scheduler
 * @brief Manages scheduling and execution of functions.
 */
class Scheduler {
 public:
  /**
   * @brief Schedules a function for execution.
   * @param func Function to be executed.
   * @param relativeTime Delay period to wait until run the scheduled function.
   */
  void scheduleFunction(ScheduledFunction func, time_t absoluteExpirationTime);

  /**
   * @brief Retrieves and removes the next scheduled function if available.
   * @param relativeTime
   * @return Functions ready to be executed.
   */
  std::vector<ScheduledFunction> popReady(std::time_t relativeTime);

  /**
   * @brief Retrieves the number of pending tasks still in the scheduler.
   * @return Number of the tasks that were scheduled but still not run.
   */
  size_t getNumPendingTasks() const;

 private:
  mutable std::mutex _mtx;
  std::priority_queue<std::time_t, std::vector<std::time_t>,
                      std::greater<std::time_t>>
      _minHeap;
  // Using the unordered_multimap to associate the scheduled time with the
  // corresponding function that will run. Another option is to use only
  // the priority_queue.
  // For example, using a std::pair<std::time_t, ScheduledFunction>.
  // To make that work, just create a custom comparator for it.
  std::unordered_multimap<std::time_t, ScheduledFunction> _scheduledFunctions;
};

}  // namespace scheduler
