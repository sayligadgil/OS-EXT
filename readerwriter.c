#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;   // for writers (exclusive access)
sem_t mutex;      // protects readCount
int readCount = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);        // lock readCount
    readCount++;
    if (readCount == 1)      // first reader blocks writers
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0)      // last reader unblocks writers
        sem_post(&rw_mutex);
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&rw_mutex);
    printf("Writer %d is writing\n", id);
    sleep(1);
    sem_post(&rw_mutex);

    return NULL;
}

int main() {
    pthread_t r1, r2, w1;

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    int a = 1, b = 2, c = 1;
    pthread_create(&r1, NULL, reader, &a);
    pthread_create(&r2, NULL, reader, &b);
    pthread_create(&w1, NULL, writer, &c);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
