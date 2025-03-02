#include <chrono>
#include <iomanip>
#include <iostream>

#include "scheduler.h"

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

void debug(scheduler::Scheduler& scheduler) {
  std::cout << "Pending tasks: " << scheduler.getNumPendingTasks() << std::endl;
}

void functionI() {
  //printTime();
  std::cout << "Task I" << std::endl;
}

void functionII() {
  //printTime();
  std::cout << "Task II" << std::endl;
}

void functionIII() {
  //printTime();
  std::cout << "Task III" << std::endl;
}

void functionIV() {
  //printTime();
  std::cout << "Task IV" << std::endl;
}

void scheduleUtil(scheduler::Scheduler& scheduler,
                  scheduler::ScheduledFunction func,
                  std::chrono::milliseconds time) {
  scheduler.scheduleFunction(func, time);
  debug(scheduler);
}

int main() {
  {
    scheduler::Dispatcher dispatcher;
    scheduler::Scheduler scheduler;

    std::cout << "Scheduling tasks ..." << std::endl;
    // scheduleUtil(scheduler, functionI, std::chrono::milliseconds(3000));

    std::cout << "Starting dispatcher" << std::endl;

    dispatcher.launch(scheduler);
    
    scheduleUtil(scheduler, functionII, std::chrono::milliseconds(8000));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    scheduleUtil(scheduler, functionIII, std::chrono::milliseconds(7000));
    scheduleUtil(scheduler, functionIII, std::chrono::milliseconds(3000));
    scheduleUtil(scheduler, functionIV, std::chrono::milliseconds(3000));
    scheduleUtil(scheduler, functionIV, std::chrono::milliseconds(4000));

    std::this_thread::sleep_for(std::chrono::milliseconds(9000));

    std::cout << "Stopping ..." << std::endl;

    dispatcher.stop();

    std::cout << "No more scheduled tasks, bye" << std::endl;
  }

  return 0;
}
