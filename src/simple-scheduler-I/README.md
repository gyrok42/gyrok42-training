# Scheduler

## Overview
The scheduler decides which function will run at a given time. It follows a simple policy: it retrieves the function that is scheduled to run at the time requested by the user.

## Scheduling a Function
The user schedules a function to run at a specific time by calling the method `scheduleFunction()`.

## Data Structures Used
The scheduler maintains the following data structures:

- **Min Heap (`min_heap`)**: Allows quick access to the next function to run (`O(1)`).
- **Unordered Map (`unordered_map`)**: Maps functions to their scheduled execution times.

## Scheduler Procedure
1. The method `pop_if()` is called.
2. The scheduler checks if the earliest scheduled function (at the top of the min heap) is ready to run.
3. If so, it retrieves and returns the function from `unordered_map`.

## Time Management
- The stored execution time is the sum of the user-provided delay and the current time.
- This computed execution time is stored in both `unordered_map` and `min_heap`.

## Dispatcher
The dispatcher retrieves scheduled functions and runs them in separate threads.

- It queries the scheduler every **1 millisecond** to maintain precision.
- Calling `runTasksAsScheduled()` keeps running until all scheduled functions are dispatched.
- Threads created by the dispatcher **detach**, meaning they are not managed after launch.
- Using `launch()`, the dispatcher runs `runTasksAsScheduled` in a separate thread.
- The dispatcher allows the main thread to continue running other tasks.
- The `join()` method can synchronize the main thread with the dispatcher.
- The scheduler is **thread-safe**, allowing new tasks to be added while the dispatcher runs.

