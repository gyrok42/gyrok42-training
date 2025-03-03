#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "dispatcher.h"
#include "scheduler.h"

std::string printTime() {
  auto now = std::chrono::system_clock::now();
  auto duration_since_epoch = now.time_since_epoch();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
      duration_since_epoch);
  std::ostringstream ostr;
  ostr << "(" << milliseconds.count() % 100000 << "): ";
  return ostr.str();
}

void functionI() {
  std::cout << printTime() << "Task I" << std::endl;
}

void functionII() {
  std::cout << printTime() << "Task II" << std::endl;
}

void functionIII() {
  std::cout << printTime() << "Task III" << std::endl;
}

void functionIV() {
  std::cout << printTime() << "Task IV" << std::endl;
}

// Another option is to define a Functor
struct MyRunnable {
  int _myParameter1;
  std::string _myParameter2;

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

std::time_t absoluteTime(std::chrono::milliseconds delay) {
  using std::chrono::system_clock;
  system_clock::time_point timePoint = system_clock::now() + delay;

  return std::chrono::system_clock::to_time_t(timePoint);
}

int main() {
  {
    using namespace std::chrono_literals;
    using namespace std::chrono;
    scheduler::Dispatcher<scheduler::Scheduler> dispatcher;
    auto scheduler = std::make_shared<scheduler::Scheduler>();

    std::cout << "Starting dispatcher" << std::endl;
    dispatcher.launch(scheduler);
    std::cout << "Scheduling tasks ..." << std::endl;

    scheduler->scheduleFunction(functionI, absoluteTime(3000ms));
    scheduler->scheduleFunction(functionII, absoluteTime(8000ms));
    std::this_thread::sleep_for(1s);
    scheduler->scheduleFunction(functionIII, absoluteTime(7000ms));
    scheduler->scheduleFunction(functionIV, absoluteTime(3000ms));
    scheduler->scheduleFunction(functionIII, absoluteTime(3000ms));
    scheduler->scheduleFunction(
        MyRunnable{._myParameter1 = 42, ._myParameter2 = "Hello!"},
        absoluteTime(8000ms));
    std::this_thread::sleep_for(9s);

    scheduler->scheduleFunction(functionI, absoluteTime(100ms));
    std::cout << "Stopping" << std::endl;
    std::this_thread::sleep_for(2s);
    // scheduler = nullptr;
    // scheduler.reset();
    // Stops the dispatcher (it will no longer spawn expiring threads).
    dispatcher.stop();

    std::cout << "No more scheduled tasks, bye: " << std::endl;
    // Problem: We don't have control over the threads spawn by the dispatcher
    // It does not guarantee that all scheduled threads have finished.
  }

  return 0;
}
