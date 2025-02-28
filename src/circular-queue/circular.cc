// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file circular.cc
 * @brief The classical FIFO implemantation utilizing a circular buffer
 * technique
 *
 * Implementing a FIFO utilizing a circular buffer technique. For this exercise
 * it is utilizing a fixed buffer size defined as a template parameter.
 *
 * Note that it uses two indixes to indicate the current "slot" for income value
 * and current "slot" for outcome value. See the illustration below:
 *
 * Suppose a BUFFER_SIZE = 5
 *
 * Empty:
 *     Buffer: [ _ ] [ _ ] [ _ ] [ _ ] [ _ ]
 *               ↑
 *              head, tail (Both point to the same empty slot)
 *
 * Note: Since we are defining the condition for "Empty" is head == tail.
 * The condition for "Full" cannot be the same.
 *
 * First insertion:
 *     Buffer: [ 10 ] [ _ ] [ _ ] [ _ ] [ _ ]
 *               ↑      ↑
 *             tail    head
 *
 * More Insertions:
 *     Buffer: [ 10 ] [ 20 ] [ 30 ] [ _ ] [ _ ]
 *               ↑                    ↑
 *             tail                  head
 *
 * After removing two items:
 *     Buffer: [ _ ] [ _ ] [ 30 ] [ _ ] [ _ ]
 *                           ↑      ↑
 *                          tail  head
 *
 * Full:
 *     Buffer: [ 23 ] [ _ ] [ 30 ] [ 12 ] [ 17 ]
 *               ↑             ↑
 *              head          tail
 *
 * Note: We cannot use head == tail as a definition of full buffer
 * since that was used as a definition for empty already.
 * Options to solve this:
 *  A. Use a count variable.
 *    Pros are 1.Explicity tracking 2.Easy to understand
 *    Cons are 1. Requires extra storage. 2. Requires update on every operation
 *  B. Keep One slot empty; Define full as next(head) == tail
 *    Pros are 1. No extra storage needed 2. Simple verification
 *    Cons is that is wastes one slot, reduces the usable capacity by 1.
 *
 * In this implementation, it is using option B (Keep One slot empty).
 * In order to make things clear for the user of the CircularQueue class,
 * the template parameter will define the real capacity, in other words,
 * defines how many items the user can count on to be stored in the FIFO.
 * Internally, we calculate the real buffer to be of size
 * _INTERNAL_BUFFER_SIZE = BUFFER_SIZE + 1.
 *
 */

#include <iostream>
#include <optional>

template <typename T, size_t BUFFER_SIZE>
class CircularQueue {
 public:
  bool empty() { return _head == _tail; }
  bool full() { return next(_head) == _tail; }
  std::optional<T> pop() {
    if (empty()) {
      return std::nullopt;
    }
    auto value = _buffer[_tail];
    _tail = next(_tail);

    return value;
  }
  bool push(T item) {
    if (full()) {
      return false;
    }
    _buffer[_head] = item;

    _head = next(_head);

    return true;
  }

 private:
  int _head{0};
  int _tail{0};
  static const size_t _INTERNAL_BUFFER_SIZE = BUFFER_SIZE + 1;
  T _buffer[_INTERNAL_BUFFER_SIZE];

  int next(int current) {
    int next = (current + 1) % _INTERNAL_BUFFER_SIZE;
    return next;
  }
};

void play_with_queue_1(CircularQueue<int, 256>& queue) {
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

void play_with_queue_2(CircularQueue<int, 256>& queue) {
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

void play_with_queue_3(CircularQueue<int, 256>& queue) {
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

void exhaust_queue(CircularQueue<int, 256>& queue) {
  std::cout << "Removing all elements in the queue" << std::endl;
  while (!queue.empty()) {
    std::cout << queue.pop().value() << ",";
  }
  std::cout << std::endl;
}

int main() {
  CircularQueue<int, 256> queue;
  play_with_queue_1(queue);
  play_with_queue_2(queue);
  play_with_queue_3(queue);
  play_with_queue_2(queue);
  exhaust_queue(queue);

  return 0;
}