#include <iostream>

#include "circular-queue3.h"

void playWithQueue_1(CircularQueue<int>& queue) {
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

void playWithQueue_2(CircularQueue<int>& queue) {
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

void playWithQueue_3(CircularQueue<int>& queue) {
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

void exhaustQueue(CircularQueue<int>& queue) {
  std::cout << "Removing all elements in the queue" << std::endl;
  while (!queue.empty()) {
    std::cout << queue.pop().value() << ",";
  }
  std::cout << std::endl;
}

int main() {
  CircularQueue<int> queue(256);
  playWithQueue_1(queue);
  playWithQueue_2(queue);
  playWithQueue_3(queue);
  playWithQueue_2(queue);
  exhaustQueue(queue);

  return 0;
}
