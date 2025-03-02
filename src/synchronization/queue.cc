// Copyright (c) 2025 gyrok42.com
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/**
 * @file queue.cc
 * @brief Basic Synchronization Patterns - Semaphore as a queue
 *
 * Queue: Semaphores can also be used to represent a queue
 * Text From: Little Book of Semaphores; Author: Allen B. Downey
 * Semaphores can also be used to represent a queue. In this case, the initial
 * value is 0, and usually the code is written so that it is not possible to
 * signal unless there is a thread waiting, so the value of the semaphore is
 * never positive. For example, imagine that threads represent ballroom dancers
 * and that two kinds of dancers, leaders and followers, wait in two queues
 * before entering the dance floor. When a leader arrives, it checks to see if
 * there is a follower waiting. If so, they can both proceed. Otherwise it
 * waits. Similarly, when a follower arrives, it checks for a leader and either
 * proceeds or waits, accordingly.
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t g_mutex;          // Controls access to shared variables
sem_t g_leaderQueue;    // Queue for g_leaders waiting for g_followers
sem_t g_followerQueue;  // Queue for g_followers waiting for g_leaders
int g_leaders = 0;      // Count leaders
int g_followers = 0;    // Count followers

void dance(long id, char type) {
  fprintf(stderr, "%c %ld: Dancing now!\n", type, id);
  usleep(500000);  // Simulate dance time
}

void* leader(void* arg) {
  long id = (long) arg;

  sem_wait(&g_mutex);  // Lock shared variables

  if (g_followers > 0) {
    g_followers--;               // Pair with a follower
    sem_post(&g_followerQueue);  // Signal follower
  } else {
    g_leaders++;  // No available g_followers, so wait
    sem_post(&g_mutex);
    sem_wait(&g_leaderQueue);
  }

  // Paired and ready to dance
  dance(id, 'L');
  sem_post(&g_mutex);  // Unlock for the next pair

  return NULL;
}

void* follower(void* arg) {
  long id = (long) arg;
  sem_wait(&g_mutex);  // Lock shared variables

  if (g_leaders > 0) {
    g_leaders--;               // Pair with a leader
    sem_post(&g_leaderQueue);  // Signal leader
  } else {
    g_followers++;  // No available g_leaders, so wait
    sem_post(&g_mutex);
    sem_wait(&g_followerQueue);
  }

  // Paired and ready to dance
  dance(id, 'F');
  sem_post(&g_mutex);  // Unlock for the next pair

  return NULL;
}

int main() {
  pthread_t threads[10];

  sem_init(&g_mutex, 0, 1);
  sem_init(&g_leaderQueue, 0, 0);
  sem_init(&g_followerQueue, 0, 0);

  // Create random g_leaders and g_followers
  std::srand(static_cast<unsigned int>(std::time(0)));
  int createdLeaders = 0;
  int createdFollowers = 0;
  for (long i = 0; i < 10; i++) {
    if (rand() % 2 == 0) {
      pthread_create(&threads[i], NULL, leader, (void*) i);
      createdLeaders++;
    } else {
      pthread_create(&threads[i], NULL, follower, (void*) i);
      createdFollowers++;
    }
    usleep(100000);  // Simulate arrival times
  }

  // Wait for all threads (Not all threads will
  // return when g_leaders != g_followers)
  fprintf(stderr, "Created leaders: %d\n", createdLeaders);
  fprintf(stderr, "Created followers: %d\n", createdFollowers);
  if (createdLeaders != createdFollowers) {
    fprintf(stderr, "Locked forever :-(\n");
  }
  for (int i = 0; i < 10; i++) pthread_join(threads[i], NULL);

  sem_destroy(&g_mutex);
  sem_destroy(&g_leaderQueue);
  sem_destroy(&g_followerQueue);

  return 0;
}
