#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxCrops 5
#define warehouseSize 5

sem_t empty;
sem_t full;

int c_index = 0;
int w_index = 0;

char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};

pthread_mutex_t mutex;

void *Farmer(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        char x = crops[c_index % warehouseSize];
        warehouse[w_index % warehouseSize] = x;

        printf("Farmer %d: Insert crops %c at %d\n", thread_id, x, w_index);

        c_index = (c_index + 1) % warehouseSize;
        w_index = (w_index + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    free(arg);
    pthread_exit(NULL);
}

void *ShopOwner(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        char y = warehouse[(w_index - 1) % warehouseSize];
        warehouse[(w_index - 1) % warehouseSize] = 'N';

        printf("Shop owner %d: Remove crops %c from %d\n", thread_id, y, (w_index - 1) % warehouseSize);

        w_index = (w_index - 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    printf("ShopOwner %d: ", thread_id);
    for (int i = 0; i < warehouseSize; i++) {
        printf("%c ", warehouse[i]);
    }
    printf("\n");

    free(arg);
    pthread_exit(NULL);
}

int main() {
    // Initialize thread, mutex, and semaphores
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        int *p = malloc(sizeof(int));
        int *q = malloc(sizeof(int));
        *p = a[i];
        *q = a[i];

        pthread_create(&Far[i], NULL, &Farmer, p);
        pthread_create(&Sho[i], NULL, &ShopOwner, q);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}