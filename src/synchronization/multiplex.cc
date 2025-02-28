// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file Basic Synchronization Patterns - Multiplex
 * @brief Limit the number of concurrent processes accessing a resource.
 *
 * Limit the number of concurrent processes accessing a
 * resource (e.g., file descriptors, network sockets, thread pools).
 *
 * Where It' Used:
 *
 * Linux process table: Limits the number of processes.
 * Web servers (Apache, Nginx): Control max concurrent requests.
 * GPU schedulers: Limit number of compute kernels.
 *
 * Illustration:
 * A parking garage can accommodate only a certain number of cars.
 * If the garage is full, new cars must wait until a spot is available.
 *
 * Synchronization Solution:
 *
 * A multiplex semaphore keeps track of available parking spots.
 * Each arriving car decrements the semaphore, and each departing
 * car increments it.
 * If no spots are available, incoming cars must wait.
 */
#include <cstdio>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 2  // Max number of threads in critical section

sem_t g_multiplex;

void* worker(void* arg) {
  // Allows up to N threads to be in the critical section
  // at the same time.
  sem_wait(&g_multiplex);  // Enter critical section
  fprintf(stderr, "Thread %ld is in critical section\n", (long) arg);
  sleep(1);
  fprintf(stderr, "Thread %ld is leaving critical section\n", (long) arg);
  sem_post(&g_multiplex);  // Exit critical section
  return NULL;
}

int main() {
  pthread_t threads[5];

  // Initializes the semaphore with the maximum number
  // of threads that can access the shared resource.
  // In this case the maximum number is N.
  sem_init(&g_multiplex, 0, N);

  // Create several threads to dispute the resource
  for (long i = 0; i < 5; i++)
    pthread_create(&threads[i], NULL, worker, (void*) i);

  for (int i = 0; i < 5; i++) pthread_join(threads[i], NULL);

  sem_destroy(&g_multiplex);
  return 0;
}
