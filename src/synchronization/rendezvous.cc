// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file rendezvous.cc
 * @brief Basic Synchronization Patterns - Rendezvous
 *
 * Rendezvous: Both threads must reach a common point before proceeding.
 * Problem: In real-time operating systems (RTOS), two tasks must complete
 * their setup phase before they execute their main operations.
 *
 * Illustration: A spacecraft and a docking station must reach a common state
 * before docking to prevent damage.
 *
 * Synchronization Solution:
 *
 * The spacecraft must reach the docking location and be stable before docking
 * begins. The docking station must be ready to receive the spacecraft.
 * Rendezvous ensures that both systems signal each other before proceeding.
 */
#include <cstdio>

#include <pthread.h>
#include <semaphore.h>

sem_t g_semA, g_semB;

// Thread A must guarantee it will run only when thread B is also ready.
// Thread B will have to know when Thread A is ready too.
// Thread A first signal Thread B that A is ready,
// then wait for ThreadB signal.
void* threadA(void* arg) {
  fprintf(stderr, "Thread A: Task A1\n");
  sem_post(&g_semA);  // Signal Thread B
  sem_wait(&g_semB);  // Wait for Thread B
  printf("Thread A: Task A2\n");
  return NULL;
}

// Thread B also must guarantee it will run only when Thread A is also ready.
// Thread A will have to know when Thread B is ready too.
// When Thread B is ready, it signals to Thread A that it is ready.
// When both have received the "ready" signal, both will run the
// corresponding code sections.
void* threadB(void* arg) {
  fprintf(stderr, "Thread B: Task B1\n");
  sem_post(&g_semB);  // Signal Thread A
  sem_wait(&g_semA);  // Wait for Thread A
  printf("Thread B: Task B2\n");
  return NULL;
}

int main() {
  pthread_t t1, t2;

  sem_init(&g_semA, 0, 0);
  sem_init(&g_semB, 0, 0);

  pthread_create(&t1, NULL, threadA, NULL);
  pthread_create(&t2, NULL, threadB, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  sem_destroy(&g_semA);
  sem_destroy(&g_semB);
  return 0;
}
