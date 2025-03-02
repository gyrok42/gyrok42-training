#include "circular-queue2.h"  // Assuming your class is in circular_queue.h
#include <gtest/gtest.h>
#include <optional>

// Define a test fixture
class CircularQueueTest : public ::testing::Test {
 protected:
  CircularQueue<int, 3> queue;  // Queue with buffer size of 3
};

// Test that a new queue is empty
TEST_F(CircularQueueTest, InitiallyEmpty) {
  EXPECT_TRUE(queue.empty());
  EXPECT_FALSE(queue.full());
}

// Test push and pop operations
TEST_F(CircularQueueTest, PushPopOperations) {
  EXPECT_TRUE(queue.push(1));
  EXPECT_FALSE(queue.empty());
  EXPECT_FALSE(queue.full());

  EXPECT_TRUE(queue.push(2));
  EXPECT_TRUE(queue.push(3));

  // Now it should be full
  EXPECT_TRUE(queue.full());

  // Attempting to push when full should fail
  EXPECT_FALSE(queue.push(4));

  // Popping elements
  auto val1 = queue.pop();
  EXPECT_TRUE(val1.has_value());
  EXPECT_EQ(val1.value(), 1);

  auto val2 = queue.pop();
  EXPECT_TRUE(val2.has_value());
  EXPECT_EQ(val2.value(), 2);

  auto val3 = queue.pop();
  EXPECT_TRUE(val3.has_value());
  EXPECT_EQ(val3.value(), 3);

  // Now the queue should be empty again
  EXPECT_TRUE(queue.empty());
}

// Test popping from an empty queue
TEST_F(CircularQueueTest, PopFromEmptyQueue) {
  EXPECT_TRUE(queue.empty());
  auto val = queue.pop();
  EXPECT_FALSE(val.has_value());  // Should return std::nullopt
}

// Test filling and then emptying the queue
TEST_F(CircularQueueTest, FillAndEmptyQueue) {
  EXPECT_TRUE(queue.push(10));
  EXPECT_TRUE(queue.push(20));
  EXPECT_TRUE(queue.push(30));

  EXPECT_TRUE(queue.full());

  EXPECT_EQ(queue.pop().value(), 10);
  EXPECT_EQ(queue.pop().value(), 20);
  EXPECT_EQ(queue.pop().value(), 30);

  EXPECT_TRUE(queue.empty());
}

// Test circular behavior (wrap-around)
TEST_F(CircularQueueTest, CircularWrapAround) {
  EXPECT_TRUE(queue.push(5));
  EXPECT_TRUE(queue.push(10));
  EXPECT_TRUE(queue.push(15));

  EXPECT_EQ(queue.pop().value(), 5);
  EXPECT_EQ(queue.pop().value(), 10);

  // Now there's space for new elements
  EXPECT_TRUE(queue.push(20));
  EXPECT_TRUE(queue.push(25));

  // Queue should now be full again
  EXPECT_TRUE(queue.full());

  EXPECT_EQ(queue.pop().value(), 15);
  EXPECT_EQ(queue.pop().value(), 20);
  EXPECT_EQ(queue.pop().value(), 25);

  EXPECT_TRUE(queue.empty());
}

// Test single element push-pop
TEST_F(CircularQueueTest, SingleElementPushPop) {
  EXPECT_TRUE(queue.push(42));
  EXPECT_FALSE(queue.empty());

  auto val = queue.pop();
  EXPECT_TRUE(val.has_value());
  EXPECT_EQ(val.value(), 42);

  EXPECT_TRUE(queue.empty());
}

// Test pushing till full and trying extra pushes
TEST_F(CircularQueueTest, PushTillFullAndExtraPush) {
  EXPECT_TRUE(queue.push(1));
  EXPECT_TRUE(queue.push(2));
  EXPECT_TRUE(queue.push(3));

  EXPECT_TRUE(queue.full());

  EXPECT_FALSE(queue.push(4));  // Should not be able to push when full
}

// Test popping all elements and then trying extra pops
TEST_F(CircularQueueTest, PopTillEmptyAndExtraPop) {
  queue.push(7);
  queue.push(8);
  queue.push(9);

  EXPECT_EQ(queue.pop().value(), 7);
  EXPECT_EQ(queue.pop().value(), 8);
  EXPECT_EQ(queue.pop().value(), 9);

  EXPECT_TRUE(queue.empty());
  EXPECT_FALSE(queue.pop().has_value());  // Should return std::nullopt
}
