// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file barrier.cc
 * @brief Basic Synchronization Patterns - Barrier
 *
 * Barrier – Race Start Synchronization
 * Problem: In an Olympic race, all runners must be at the starting line
 * and wait for the gunshot before starting the race.
 *
 * Synchronization Solution:
 *
 * A barrier ensures that no runner starts before all are ready.
 * The race gun (triggered by the referee) is released only after all runners
 * reach the starting line.
 *
 * Turnstile:
 * Threads increment a counter as they arrive.
 * When all threads arrive, a turnstile semaphore opens.
 * Each thread must pass through the turnstile one at a time.
 */

#include <cstdio>

#include <pthread.h>
#include <semaphore.h>

#define N 3

sem_t g_mutex, g_barrier;
int count = 0;

// All the threads must be ready so that all threads may start
void* worker(void* arg) {
  fprintf(stderr, "Thread %ld reached g_barrier\n", (long) arg);
  // A Mutex is used to ensure the counter is consistent (see mutex pattern).
  sem_wait(&g_mutex);  // lock mutex
  // This thread is ready, increment the count of ready threads.
  count++;
  // When all N expected threads are ready, release the barrier.
  if (count == N)
    sem_post(&g_barrier);  // Release g_barrier when all threads arrive
  sem_post(&g_mutex);      // unlock mutex

  // Before the first sem_post(&g_barrier),
  // all threads arriving here will be blocked.
  sem_wait(&g_barrier);  // Ensure all threads wait
  // The first thread to pass will block the other threads,
  // Release for the next thread to pass.
  sem_post(&g_barrier);  // Turnstile: Ensures only one thread passes at a time
  // That pattern wait (sem_wait) and a signal (sem_post) in rapid succession is
  // called Turnstile.

  fprintf(stderr, "Thread %ld passed g_barrier\n", (long) arg);
  return NULL;
}

int main() {
  pthread_t threads[N];

  sem_init(&g_mutex, 0, 1);
  sem_init(&g_barrier, 0, 0);

  for (long i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, worker, (void*) i);

  for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);

  sem_destroy(&g_mutex);
  sem_destroy(&g_barrier);
  return 0;
}
