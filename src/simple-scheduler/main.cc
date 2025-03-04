// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file main.cc
 * @brief Playing with dispatcher and scheduler
 *
 */
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "dispatcher.h"
#include "scheduler.h"

/**
 * @brief Gets the current system time in milliseconds and formats it as a
 * string.
 *
 * @return A formatted string with the last 5 digits of the milliseconds count.
 */
std::string printTime() {
  auto now = std::chrono::system_clock::now();
  auto duration_since_epoch = now.time_since_epoch();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
      duration_since_epoch);
  std::ostringstream ostr;
  ostr << "(" << milliseconds.count() % 100000 << "): ";
  return ostr.str();
}

/**
 * @brief Function that prints "Task I" with a timestamp.
 */
void functionI() {
  std::cout << printTime() << "Task I" << std::endl;
}

/**
 * @brief Function that prints "Task II" with a timestamp.
 */
void functionII() {
  std::cout << printTime() << "Task II" << std::endl;
}

/**
 * @brief Function that prints "Task III" with a timestamp.
 */
void functionIII() {
  std::cout << printTime() << "Task III" << std::endl;
}

/**
 * @brief Function that prints "Task IV" with a timestamp.
 */
void functionIV() {
  std::cout << printTime() << "Task IV" << std::endl;
}

/**
 * @brief A functor (callable object) that simulates a runnable task.
 */
struct MyRunnable {
  int _myParameter1;          ///< First parameter of the runnable task.
  std::string _myParameter2;  ///< Second parameter of the runnable task.

  /**
   * @brief Overloaded function call operator to execute the runnable task.
   *
   * This function simulates work with a delay and prints task details.
   */
  void operator()() {
    std::cout << ::printTime() << "MyRunnable" << std::endl;
    std::cout << "\t\tRunning my thread" << std::endl;
    std::cout << "\t\tParameter1: " << _myParameter1 << std::endl;
    std::cout << "\t\tParameter2: " << _myParameter2 << std::endl;
    std::cout << "\t\tMyRunnable Working ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\t\tFinished, bye" << std::endl;
  }
};

/**
 * @brief Computes an absolute expiration time based on a delay.
 *
 * @param delay The duration in milliseconds after which the task should
 * execute.
 * @return std::time_t The absolute time when the task should be executed.
 */
std::time_t absoluteTime(std::chrono::milliseconds delay) {
  using std::chrono::system_clock;
  system_clock::time_point timePoint = system_clock::now() + delay;

  return std::chrono::system_clock::to_time_t(timePoint);
}

/**
 * @brief demo function that demonstrates the scheduling and dispatching of
 * tasks.
 *
 * The function:
 * - Initializes a scheduler and dispatcher.
 * - Schedules multiple tasks with different execution times.
 * - Uses absolute expiration times for scheduling.
 * - Simulates execution delays with `sleep_for`.
 * - Stops the dispatcher before exiting.
 *
 */
void demo() {
  using namespace std::chrono_literals;
  using namespace std::chrono;

  // Create dispatcher and scheduler
  scheduler::Dispatcher<scheduler::Scheduler> dispatcher;
  auto scheduler = std::make_shared<scheduler::Scheduler>();

  std::cout << "Starting dispatcher" << std::endl;
  dispatcher.launch(scheduler);
  std::cout << "Scheduling tasks ..." << std::endl;

  // Scheduling functions at absolute times
  scheduler->scheduleFunction(functionI, absoluteTime(3000ms));
  scheduler->scheduleFunction(functionII, absoluteTime(8000ms));
  std::this_thread::sleep_for(1s);
  scheduler->scheduleFunction(functionIII, absoluteTime(7000ms));
  scheduler->scheduleFunction(functionIV, absoluteTime(3000ms));
  scheduler->scheduleFunction(functionIII, absoluteTime(3000ms));

  // Scheduling a functor (MyRunnable)
  scheduler->scheduleFunction(
      MyRunnable{._myParameter1 = 42, ._myParameter2 = "Hello!"},
      absoluteTime(8000ms));

  std::this_thread::sleep_for(9s);

  // Scheduling another task after some delay
  scheduler->scheduleFunction(functionI, absoluteTime(100ms));

  std::cout << "Stopping" << std::endl;
  std::this_thread::sleep_for(2s);

  // Stops the dispatcher (it will no longer spawn expiring threads).
  dispatcher.stop();

  std::cout << "No more scheduled tasks, bye: " << std::endl;
  // Problem: We don't have control over the threads spawned by the dispatcher.
  // It does not guarantee that all scheduled threads have finished.
}

int main() {
  demo();
  return 0;
}
