// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Basic Synchronization Patterns
// Mutex: Mutual exclusion
// Problem: Prevent race conditions
// in shared resources such as file system operations, shared memory,
// or critical sections.
// Illustration:
// Two users trying to withdraw money from the same bank account at the
// same time can lead to incorrect balance updates.
//
// Synchronization Solution:
//
// The bank enforces mutex on the shared bank balance.
// If one user is withdrawing money, the system locks the balance to
// prevent another transaction from happening simultaneously.
// Once the first transaction completes, the mutex is released for the next
// user.

#include <cstdio>

#include <pthread.h>
#include <semaphore.h>

sem_t g_mutex;
int g_counter = 0;

// Several threads are calling the increment.
// We make the safe assumption that the increment operation is not atomic.
// Suppose:
// temp = counter
// counter = temp + 1
// That non-atomic operation described above will lead no inconsistencies.
// The temp can be the same in two separate threads and only one
// operation will be counted.
// The mutex pattern creates a "critica area" where only on thread at a time
// can perform that operation.
// The entrance of the critical area is defined by a lock
// The exit of the cricital are is defined by an unlock
void* increment(void* arg) {
  sem_wait(&g_mutex);  // Lock
  g_counter++;
  fprintf(stderr, "Thread %ld: Counter = %d\n", (long) arg, g_counter);
  sem_post(&g_mutex);  // Unlock
  return NULL;
}

int main() {
  pthread_t t1, t2;

  sem_init(&g_mutex, 0, 1);

  pthread_create(&t1, NULL, increment, (void*) 1);
  pthread_create(&t2, NULL, increment, (void*) 2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  sem_destroy(&g_mutex);
  return 0;
}
