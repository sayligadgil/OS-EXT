#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5    // number of philosophers

sem_t forks[N];     // fork semaphores
sem_t mutex;        // waiter semaphore

void *philosopher(void *num) {
    int i = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);

        sem_wait(&mutex);               // ask waiter
        sem_wait(&forks[i]);            // pick left fork
        sem_wait(&forks[(i+1)%N]);      // pick right fork
        sem_post(&mutex);

        printf("Philosopher %d is eating\n", i);
        sleep(1);

        sem_post(&forks[i]);
        sem_post(&forks[(i+1)%N]);

        printf("Philosopher %d finished eating\n", i);
    }
}

int main() {
    pthread_t tid[N];
    int index[N];

    // initialize waiter
    sem_init(&mutex, 0, 1);

    // initialize 5 forks
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        index[i] = i;
    }

    // create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, &index[i]);
    }

    // join threads
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }
}
