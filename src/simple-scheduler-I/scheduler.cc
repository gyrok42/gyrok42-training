// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file scheduler.cc
 * @brief Function Scheduler Implementation
 *
 * This scheduler is designed to execute functions only once at their scheduled
 * time with a precision of 1 millisecond.
 *
 * Features:
 * - Allows adding functions with specific execution times.
 * - Ensures only one function is scheduled at a given time.
 * - Uses a Dispatcher class to handle threaded execution.
 * - Implements a Scheduler class to manage function scheduling.
 */

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <unordered_map>

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
   * @param time_point Delay period to wait until run the scheduled function. 
   * @return true if scheduled successfully, false if time slot is occupied.
   */
  bool scheduleFunction(ScheduledFunction func,
                        std::chrono::milliseconds delay) {
    std::chrono::system_clock::time_point time_point_then =
        std::chrono::system_clock::now() + delay;
    // Convert time_point to time_t
    std::time_t time_t_from_time_point =
        std::chrono::system_clock::to_time_t(time_point_then);

    bool ret = false;
    std::lock_guard<std::mutex> guard(_mtx);
    auto insertRet = _scheduledFunctions.insert({time_t_from_time_point, func});
    if (insertRet.second) {
      _minHeap.push(time_t_from_time_point);
      ret = true;
    }

    return ret;
  }

  /**
   * @brief Retrieves and removes the next scheduled function if available.
   * @return An optional function to be executed.
   */
  std::optional<ScheduledFunction> pop_if() {
    std::chrono::system_clock::time_point time_point_now =
        std::chrono::system_clock::now();
    std::time_t time_t_from_time_point =
        std::chrono::system_clock::to_time_t(time_point_now);
    std::optional<ScheduledFunction> ret = std::nullopt;
    std::lock_guard<std::mutex> guard(_mtx);

    auto next = _minHeap.top();
    if (next <= time_t_from_time_point) {
      _minHeap.pop();
      ret = _scheduledFunctions[next];
      _scheduledFunctions.erase(next);
    }

    return ret;
  }

  /**
   * @brief Retrieves the number of pending tasks still in the scheduler.
   * @return Number of the tasks that were scheduled but still not run.
   */
  size_t getNumPendingTasks() const {
    std::lock_guard<std::mutex> guard(_mtx);
    return _minHeap.size();
  }

 private:
  mutable std::mutex _mtx;
  std::priority_queue<std::time_t, std::vector<std::time_t>,
                      std::greater<std::time_t>>
      _minHeap;

  std::unordered_map<std::time_t, ScheduledFunction> _scheduledFunctions;
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
   */
  void launch(Scheduler& scheduler) {
    _tasksRunner = std::make_unique<std::thread>(
        &Dispatcher::runTasksAsScheduled, this, std::ref(scheduler));
  }

  /**
   * @brief Executes scheduled tasks as per the scheduler's queue.
   * @param scheduler Reference to the scheduler managing tasks.
   */
  void runTasksAsScheduled(Scheduler& scheduler) {
    while (scheduler.getNumPendingTasks()) {
      auto func = scheduler.pop_if();
      if (func) {
        std::thread scheduledFunction(func.value());
        scheduledFunction.detach();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }

  void join() {
    if (_tasksRunner != nullptr) {
      _tasksRunner->join();
      _tasksRunner = nullptr;
    }
  }

 private:
  std::unique_ptr<std::thread> _tasksRunner;
};

void printTime() {
  // Get the current time point
  auto now = std::chrono::system_clock::now();

  // Convert to a time_t (seconds precision)
  auto time_t_now = std::chrono::system_clock::to_time_t(now);

  // Convert to local time
  std::tm local_tm = *std::localtime(&time_t_now);

  // Extract milliseconds
  auto duration_since_epoch = now.time_since_epoch();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                          duration_since_epoch) %
                      1000;

  // Print formatted time
  std::cout << std::put_time(&local_tm,
                             "%H:%M:%S")  // Print hours, minutes, and seconds
            << ":" << std::setw(3) << std::setfill('0')
            << milliseconds.count()  // Print milliseconds
            << ": ";
}

void taskI() {
  printTime();
  std::cout << "Task I" << std::endl;
}

void taskII() {
  printTime();
  std::cout << "Task II" << std::endl;
}

void taskIII() {
  printTime();
  std::cout << "Task III" << std::endl;
}

void scheduleUtil(Scheduler& scheduler, ScheduledFunction func,
                  std::chrono::milliseconds time) {
  if (!scheduler.scheduleFunction(func, time)) {
    std::cout << "Failed scheduling process" << std::endl;
  }
}

int main() {
  Dispatcher dispatcher;
  Scheduler scheduler;

  std::cout << "Scheduling tasks ..." << std::endl;
  scheduleUtil(scheduler, taskI, std::chrono::milliseconds(3000));
  dispatcher.launch(scheduler);
  scheduleUtil(scheduler, taskII, std::chrono::milliseconds(8000));
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  scheduleUtil(scheduler, taskIII, std::chrono::milliseconds(7000));
  scheduleUtil(scheduler, taskIII, std::chrono::milliseconds(3000));

  std::cout << "Starting dispatcher" << std::endl;

  dispatcher.join();

  std::cout << "No more scheduled tasks, bye" << std::endl;

  return 0;
}
