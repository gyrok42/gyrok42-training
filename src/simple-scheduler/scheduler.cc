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
 */
#include "scheduler.h"

namespace scheduler {
using ScheduledFunction = std::function<void()>;

std::time_t absoluteTime(std::chrono::milliseconds delay) {
  using std::chrono::system_clock;
  system_clock::time_point timePoint = system_clock::now() + delay;

  return std::chrono::system_clock::to_time_t(timePoint);
}

void Scheduler::scheduleFunction(ScheduledFunction func,
                                 std::chrono::milliseconds delay) {
  auto expirationTime = absoluteTime(delay);

  std::lock_guard<std::mutex> guard(_mtx);
  auto iterator = _scheduledFunctions.find(expirationTime);
  if (std::end(_scheduledFunctions) == iterator) {
    _minHeap.push(expirationTime);
  }
  _scheduledFunctions.insert({expirationTime, func});
}

std::vector<ScheduledFunction> Scheduler::popExpiringFunctions(
    std::time_t time_point) {
  std::vector<ScheduledFunction> expiringFunctions;
  std::lock_guard<std::mutex> guard(_mtx);

  auto next = _minHeap.top();
  if (next <= time_point) {
    _minHeap.pop();
    auto range = _scheduledFunctions.equal_range(next);
    for (auto it = range.first; it != range.second; it++) {
      expiringFunctions.push_back(it->second);
    }
    _scheduledFunctions.erase(time_point);
  }

  return expiringFunctions;
}

/**
 * @brief Retrieves the number of pending tasks still in the scheduler.
 * @return Number of the tasks that were scheduled but still not run.
 */
size_t Scheduler::getNumPendingTasks() const {
  std::lock_guard<std::mutex> guard(_mtx);
  return _scheduledFunctions.size();
}

bool Dispatcher::launch(Scheduler& scheduler) {
  if (_tasksRunner != nullptr) {
    return false;
  }
  _tasksRunner = std::make_unique<std::thread>(&Dispatcher::runTasksAsScheduled,
                                               this, std::ref(scheduler));
  return true;
}

void dispatcherWrapper(ScheduledFunction func) {
  func();
}

void Dispatcher::runTasksAsScheduled(Scheduler& scheduler) {
  using std::chrono::system_clock;
  for (;;) {
    time_t timeNow = system_clock::to_time_t(system_clock::now());
    auto functions = scheduler.popExpiringFunctions(timeNow);
    for (auto func : functions) {
      _threads.emplace_back(std::thread{dispatcherWrapper, func});
    }
    if (_stopFlag.load()) {
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  for (auto& thread : _threads) {
    thread.join();
  }
  _threads.clear();
}

void Dispatcher::stop() {
  _stopFlag.store(true);

  if (_tasksRunner != nullptr) {
    _tasksRunner->join();
  }
}

}  // namespace scheduler
