#include <iostream>

#include "circular-queue3.h"

void play_with_queue_1(CircularQueue<int>& queue) {
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

void play_with_queue_2(CircularQueue<int>& queue) {
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

void play_with_queue_3(CircularQueue<int>& queue) {
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

void exhaust_queue(CircularQueue<int>& queue) {
  std::cout << "Removing all elements in the queue" << std::endl;
  while (!queue.empty()) {
    std::cout << queue.pop().value() << ",";
  }
  std::cout << std::endl;
}

int main() {
  CircularQueue<int> queue(256);
  play_with_queue_1(queue);
  play_with_queue_2(queue);
  play_with_queue_3(queue);
  play_with_queue_2(queue);
  exhaust_queue(queue);

  return 0;
}
