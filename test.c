#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 200 // You can change this to any number up to 200

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* arg)
{
    int id = *(int*)arg;
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Think for a while
        printf("Philosopher %d is thinking\n", id);
        usleep(rand() % 1000000);

        // Pick up left chopstick
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", id, left_chopstick);

        // Pick up right chopstick
        pthread_mutex_lock(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", id, right_chopstick);

        // Eat for a while
        printf("Philosopher %d is eating\n", id);
        usleep(rand() % 1000000);

        // Put down right chopstick
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d put down right chopstick %d\n", id, right_chopstick);

        // Put down left chopstick
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        printf("Philosopher %d put down left chopstick %d\n", id, left_chopstick);
    }
}

int main(int argc, char* argv[])
{
    int i;

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_init(&chopsticks[i], NULL) != 0) {
            fprintf(stderr, "Failed to initialize mutex %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Create threads for philosophers
    pthread_t philosophers[NUM_PHILOSOPHERS];
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* arg = malloc(sizeof(*arg));
        *arg = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, arg) != 0) {
            fprintf(stderr, "Failed to create thread for philosopher %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for philosophers to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread for philosopher %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Destroy mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_destroy(&chopsticks[i]) != 0) {
            fprintf(stderr, "Failed to destroy mutex %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
