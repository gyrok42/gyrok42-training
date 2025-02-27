// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Basic Synchronization Patterns
// Signaling: One thread sends a signal to another thread
// to indicate that something has happened.
// It makes possible to to guarantee that a section in one
// code in one thread will run before a section of code in
// another thread.
// Solves the serialization problem.

#include <cstdio>

#include <pthread.h>
#include <semaphore.h>

sem_t g_sem;

// Thread A: We want to have a section of code on A that
// runs before a section of code on Thread B
void* threadA(void* arg) {
  // First execute Thread A desired code section
  fprintf(stderr, "Thread A: Executing task A1\n");
  // Now allows thread B section of code to run
  sem_post(&g_sem);  // Signal Thread B
  return NULL;
}

// Thread B: We want to wait for a section of code in thread A
// to run before running the section of code in Thread B.
void* threadB(void* arg) {
  // Before running, waits Thread A to signal
  sem_wait(&g_sem);  // Wait for signal from Thread A
  // Run the section of code of thread B
  fprintf(stderr, "Thread B: Executing task B1 after A1\n");
  return NULL;
}

// Initializing the semaphore and threads.
// Launching, waiting threads to finish.
// Release semaphore.
int main() {
  pthread_t t1, t2;

  sem_init(&g_sem, 0, 0);
  pthread_create(&t1, NULL, threadA, NULL);
  pthread_create(&t2, NULL, threadB, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  sem_destroy(&g_sem);
  return 0;
}
