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
                                 std::chrono::milliseconds relativeTime) {
  using std::chrono::system_clock;
  auto expirationTime =
      system_clock::to_time_t(system_clock::now() + relativeTime);

  std::lock_guard<std::mutex> guard(_mtx);
  auto iterator = _scheduledFunctions.find(expirationTime);
  if (std::end(_scheduledFunctions) == iterator) {
    _minHeap.push(expirationTime);
  }
  _scheduledFunctions.insert({expirationTime, func});
}

std::vector<ScheduledFunction> Scheduler::popReady(
    std::time_t absoluteTimeNow) {
  std::vector<ScheduledFunction> expiringFunctions;
  std::lock_guard<std::mutex> guard(_mtx);

  auto next = _minHeap.top();
  if (next <= absoluteTimeNow) {
    _minHeap.pop();
    auto range = _scheduledFunctions.equal_range(next);
    for (auto it = range.first; it != range.second; it++) {
      expiringFunctions.push_back(it->second);
    }
    _scheduledFunctions.erase(absoluteTimeNow);
  }

  return expiringFunctions;
}

size_t Scheduler::getNumPendingTasks() const {
  std::lock_guard<std::mutex> guard(_mtx);
  return _scheduledFunctions.size();
}

}  // namespace scheduler
