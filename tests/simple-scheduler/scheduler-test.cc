#include "scheduler.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>

namespace scheduler {

// Mockable clock class
class MockClock {
 public:
  MOCK_METHOD(std::time_t, now, (), (const));
};

// Global mock clock instance
MockClock* global_mock_clock = nullptr;

// Replacement for std::time(nullptr)
std::time_t mock_time() {
  return global_mock_clock ? global_mock_clock->now() : std::time(nullptr);
}

// Test Fixture for Scheduler
class SchedulerTest : public ::testing::Test {
 protected:
  Scheduler scheduler;
  testing::NiceMock<MockClock> mockClock;

  void SetUp() override { global_mock_clock = &mockClock; }

  void TearDown() override { global_mock_clock = nullptr; }
};

// Test scheduling a function and checking pending task count
TEST_F(SchedulerTest, ScheduleFunctionIncreasesPendingTasks) {
  scheduler.scheduleFunction([]() {}, 100);
  EXPECT_EQ(scheduler.getNumPendingTasks(), 1);
}

// Test popping a scheduled function when it's ready
TEST_F(SchedulerTest, PopReadyReturnsScheduledFunction) {
  bool executed = false;
  scheduler.scheduleFunction([&executed]() { executed = true; }, 100);

  // Mock time progression
  EXPECT_CALL(mockClock, now()).WillRepeatedly(testing::Return(100));

  // Pop the ready function
  auto readyFunctions = scheduler.popReady(100);

  ASSERT_EQ(readyFunctions.size(), 1);
  readyFunctions[0]();  // Execute the function
  EXPECT_TRUE(executed);
}

// Test that function is not popped too early
TEST_F(SchedulerTest, PopReadyDoesNotReturnFunctionTooEarly) {
  bool executed = false;
  scheduler.scheduleFunction([&executed]() { executed = true; }, 500);

  // Attempt to pop functions before they are due
  auto readyFunctions = scheduler.popReady(499);

  EXPECT_TRUE(readyFunctions.empty());
}

// Test scheduling multiple functions with different absolute times
TEST_F(SchedulerTest, MultipleFunctionsAreScheduledAndExecutedInOrder) {
  std::vector<int> executionOrder;
  scheduler.scheduleFunction([&]() { executionOrder.push_back(1); }, 1000);
  scheduler.scheduleFunction([&]() { executionOrder.push_back(2); }, 2000);
  scheduler.scheduleFunction([&]() { executionOrder.push_back(2); }, 3000);

  auto firstBatch = scheduler.popReady(1000);
  ASSERT_EQ(firstBatch.size(), 1);
  firstBatch[0]();

  auto secondBatch = scheduler.popReady(2001);
  ASSERT_EQ(secondBatch.size(), 1);
  secondBatch[0]();

  auto thirdBatch = scheduler.popReady(2999);
  ASSERT_EQ(thirdBatch.size(), 0);

  EXPECT_EQ(executionOrder, std::vector<int>({1, 2}));
}

}  // namespace scheduler
