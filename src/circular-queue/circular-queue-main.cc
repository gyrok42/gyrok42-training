#include <iostream>

#include "circular-queue.h"

template <std::size_t Size>
void playWithQueue1(CircularQueue<int, Size>& queue) {
  std::cout << "Trying to pop a value" << std::endl;
  auto value = queue.pop();
  if (!value) {
    std::cout << "Not able to get value from empty queue (OK)" << std::endl;
  }

  std::cout << "Filling up" << std::endl;
  int i = 0;
  while (!queue.full()) {
    queue.push(i);
    i++;
  }
  std::cout << "Inserted " << i << " elements. See" << std::endl;

  while (!queue.empty()) {
    std::cout << queue.pop().value() << ",";
  }
  std::cout << std::endl;
}

template <std::size_t Size>
void playWithQueue2(CircularQueue<int, Size>& queue) {
  auto value = queue.pop();
  if (!value) {
    std::cout << "Not able to get value from empty queue (OK)" << std::endl;
  }

  int i = 0;
  while (!queue.full()) {
    queue.push(i);
    i++;
  }
  std::cout << "Inserted " << i << " elements." << std::endl;
  std::cout << "Poping few items" << std::endl;
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";

  std::cout << std::endl;
}

template <std::size_t Size>
void playWithQueue3(CircularQueue<int, Size>& queue) {
  auto value = queue.pop();
  if (!value) {
    std::cout << "Not able to get value from empty queue (OK)" << std::endl;
  }

  std::cout << "Poping few items" << std::endl;
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";
  std::cout << queue.pop().value() << ",";

  if (queue.push(-5)) {
    std::cout << "push success" << std::endl;
  }

  std::cout << std::endl;
}

template <std::size_t Size>
void exhaustQueue(CircularQueue<int, Size>& queue) {
  std::cout << "Removing all elements in the queue" << std::endl;
  while (!queue.empty()) {
    std::cout << queue.pop().value() << ",";
  }
  std::cout << std::endl;
}

void circularQueue1() {
  CircularQueue<int, 256> queue;
  playWithQueue1(queue);
  playWithQueue2(queue);
  playWithQueue3(queue);
  playWithQueue2(queue);
  exhaustQueue(queue);
}

int main() {
  circularQueue1();

  return 0;
}