// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file reusable_barrier.cc
 * @brief Basic Synchronization Patterns - Reusable barrier
 *
 * This implementation of a reusable barrier ensures that after all threads 
 * have passed through, the turnstile is locked again.
 * 
 * The solution is sometimes called a two-phase barrier because it forces all
 * the threads to wait twice:
 * 1. Only the Nth thread can lock or unlock the turnstiles.
 * 2. Before a thread can unlock the first turnstile, it has to close the
 *    second, and vice versa; therefore, it is impossible for one thread to get
 *    ahead of the others by more than one turnstile.
 */

 #include <cstdio>
 #include <pthread.h>
 #include <semaphore.h>
 
 #define N 3  ///< Number of worker threads
 
 sem_t g_mutex, g_turnstile1, g_turnstile2; ///< Synchronization semaphores
 int g_count = 0; ///< Count of threads reaching the barrier
 int g_passed_debug[N]{0, 0, 0}; ///< Debugging array to track barrier passes
 
 /**
  * @brief Worker function executed by each thread.
  *
  * Each thread repeatedly reaches the barrier, waits for all threads to arrive, 
  * then passes through it in a synchronized manner. The two-phase mechanism 
  * ensures no thread gets ahead of others beyond a single barrier pass.
  *
  * @param arg Thread identifier (cast from long integer).
  * @return Always returns NULL.
  */
 void* worker(void* arg) {
   for (int i = 0; i < 100; i++) {
     fprintf(stderr, "Thread %ld reached barrier\n", (long) arg);
 
     // Phase 1: Synchronization before passing the barrier
     sem_wait(&g_mutex);
     g_count++;
     if (g_count == N) {
       sem_wait(&g_turnstile2);  // Close the second turnstile
       sem_post(&g_turnstile1);  // Open the first turnstile
     }
     sem_post(&g_mutex);
 
     sem_wait(&g_turnstile1); // Wait for the first turnstile to open
     sem_post(&g_turnstile1); // Ensure all threads can pass
 
     fprintf(stderr, "Thread %ld passed barrier\n", (long) arg);
     g_passed_debug[(long) arg]++;
 
     // Phase 2: Reset barrier for next iteration
     sem_wait(&g_mutex);
     g_count--;
     if (g_count == 0) {
       sem_wait(&g_turnstile1); // Close the first turnstile
       sem_post(&g_turnstile2); // Open the second turnstile
     }
     sem_post(&g_mutex);
 
     sem_wait(&g_turnstile2); // Wait for the second turnstile to open
     sem_post(&g_turnstile2); // Ensure all threads can pass
   }
   return NULL;
 }
 
 /**
  * @brief Main function to initialize and execute threads.
  *
  * The function initializes semaphores, creates worker threads, waits for them
  * to complete, then cleans up resources. It also prints debug information
  * about the number of times each thread successfully passed the barrier.
  *
  * @return 0 upon successful execution.
  */
 int main() {
   pthread_t threads[N];
 
   // Initialize semaphores
   sem_init(&g_mutex, 0, 1);
   sem_init(&g_turnstile1, 0, 0);
   sem_init(&g_turnstile2, 0, 1); // Start open for initial execution
 
   // Create worker threads
   for (long i = 0; i < N; i++)
     pthread_create(&threads[i], NULL, worker, (void*) i);
 
   // Wait for all threads to complete
   for (int i = 0; i < N; i++)
     pthread_join(threads[i], NULL);
 
   // Destroy semaphores
   sem_destroy(&g_mutex);
   sem_destroy(&g_turnstile1);
   sem_destroy(&g_turnstile2);
 
   // Print debugging information
   for (int i = 0; i < N; i++) {
     fprintf(stderr, "g_passed_debug[%d] = %d\n", i, g_passed_debug[i]);
   }
 
   return 0;
 }
 