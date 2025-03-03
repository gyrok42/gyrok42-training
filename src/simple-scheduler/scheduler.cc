// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file scheduler.cc
 * @brief Function Scheduler Implementation
 *
 * This scheduler is designed to execute functions only
 * once at their scheduled.
 * time with a precision of 1 millisecond.
 *
 */

#include "scheduler.h"

namespace scheduler {
using ScheduledFunction = std::function<void()>;

void Scheduler::scheduleFunction(ScheduledFunction func,
                                 time_t absoluteExpirationTime) {
  std::lock_guard<std::mutex> guard(_mtx);
  _minHeap.push(
      ScheduleInfo{.expirationTime = absoluteExpirationTime, .function = func});
}

std::vector<ScheduledFunction> Scheduler::popReady(
    std::time_t absoluteTimeNow) {
  std::vector<ScheduledFunction> expiringFunctions;
  std::lock_guard<std::mutex> guard(_mtx);

  while (!_minHeap.empty()) {
    if (auto next = _minHeap.top(); next.expirationTime <= absoluteTimeNow) {
      _minHeap.pop();
      expiringFunctions.push_back(next.function);
    } else {
      break;
    }
  }

  return expiringFunctions;
}

size_t Scheduler::getNumPendingTasks() const {
  std::lock_guard<std::mutex> guard(_mtx);
  return _minHeap.size();
}

}  // namespace scheduler
