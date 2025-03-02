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
   * @brief Default constructor.
   */
  Scheduler() {}
  /**
   * @brief Default destructor.
   */
  ~Scheduler() {}

  /**
   * @brief Schedules a function for execution.
   * @param func Function to be executed.
   * @param timePoint Delay period to wait until run the scheduled function.
   */
  void scheduleFunction(ScheduledFunction func,
                        std::chrono::milliseconds delay);

  /**
   * @brief Retrieves and removes the next scheduled function if available.
   * @return An optional function to be executed.
   */
  std::vector<ScheduledFunction> popExpiringFunctions(std::time_t timePoint);

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

/**
 * @class Dispatcher
 * @brief Manages execution of scheduled tasks in separate threads.
 */
class Dispatcher {
 public:
  /**
   * @brief Default constructor.
   */
  Dispatcher() {}
  /**
   * @brief Default destructor.
   */
  ~Dispatcher() {}

  /**
   * @brief Launches a scheduler in a separate thread.
   * @param scheduler Reference to the scheduler managing tasks.
   * @return true if success, otherwise false.
   * If it has already been launched but not stopped,
   * the launch will not re-launch. It will return false.
   */
  bool launch(Scheduler& scheduler);

  /**
   * @brief Executes scheduled tasks as per the scheduler's queue.
   * @param scheduler Reference to the scheduler managing tasks.
   */
  void runTasksAsScheduled(Scheduler& scheduler);

  void stop();

 private:
  std::unique_ptr<std::thread> _tasksRunner;
  std::atomic<bool> _stopFlag{false};
  std::vector<std::thread> _threads;
};

}  // namespace scheduler
