#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;   // empty slots
sem_t full;    // filled slots
sem_t mutex;   // mutual exclusion

void* producer(void* arg) {
    int item = 1;

    while (1) {
        sem_wait(&empty);     // wait if buffer full
        sem_wait(&mutex);     // lock

        buffer[in] = item;
        printf("Producer produced %d at %d\n", item, in);
        in = (in + 1) % SIZE;
        item++;

        sem_post(&mutex);     // unlock
        sem_post(&full);      // increase filled slots
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;

    while (1) {
        sem_wait(&full);      // wait if buffer empty
        sem_wait(&mutex);     // lock

        item = buffer[out];
        printf("Consumer consumed %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        sem_post(&mutex);     // unlock
        sem_post(&empty);     // increase empty slots
        sleep(1);
    }
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
