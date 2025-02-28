// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file reusable_barrier.cc
 * @brief Basic Synchronization Patterns - Reusable barrier
 *
 * Rewrite the barrier solution so that after all the threads have passed
 * through, the turnstile is locked again.
 * This solution is sometimes called a two-phase barrier because it forces all
 * the threads to wait twice
 * 1. Only the Nth thread can lock or unlock the turnstiles.
 * 2. Before a thread can unlock the first turnstile, it has to close the
 * second,
 *    and vice versa; therefore it is impossible for one thread to get ahead of
 *    the others by more than one turnstile.
 */
#include <cstdio>

#include <pthread.h>
#include <semaphore.h>

#define N 3

sem_t g_mutex, g_turnstile1, g_turnstile2;
int g_count = 0;
int g_passed_debug[N]{0, 0, 0};

void* worker(void* arg) {
  for (int i = 0; i < 100; i++) {
    fprintf(stderr, "Thread %ld reached barrier\n", (long) arg);
    // Phase 1
    sem_wait(&g_mutex);
    g_count++;
    if (g_count == N) {
      sem_wait(&g_turnstile2);
      sem_post(&g_turnstile1);
    }
    sem_post(&g_mutex);

    sem_wait(&g_turnstile1);
    sem_post(&g_turnstile1);

    fprintf(stderr, "Thread %ld passed barrier\n", (long) arg);
    g_passed_debug[(long) arg]++;

    // Phase 2
    sem_wait(&g_mutex);
    g_count--;
    if (g_count == 0) {
      sem_wait(&g_turnstile1);
      sem_post(&g_turnstile2);
    }
    sem_post(&g_mutex);

    sem_wait(&g_turnstile2);
    sem_post(&g_turnstile2);
  }
  return NULL;
}

int main() {
  pthread_t threads[N];

  sem_init(&g_mutex, 0, 1);
  sem_init(&g_turnstile1, 0, 0);
  // Initialize the second turnstile with 1
  // So that the very first time it is not blocked
  // It is like a previous second phase had finished
  sem_init(&g_turnstile2, 0, 1);

  for (long i = 0; i < N; i++)
    pthread_create(&threads[i], NULL, worker, (void*) i);

  for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);

  sem_destroy(&g_mutex);
  sem_destroy(&g_turnstile1);
  sem_destroy(&g_turnstile2);

  for (int i = 0; i < N; i++) {
    fprintf(stderr, "g_passed_debug[%d] = %d\n", i, g_passed_debug[i]);
  }
  return 0;
}
