#include <stdio.h>
#include <pthread.h>

void* runThread(void* arg) {
    int id = *(int*)arg;
    printf("Thread-%d running\n", id);
    printf("Thread-%d closed\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, runThread, &ids[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}