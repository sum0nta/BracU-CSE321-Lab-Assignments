#include <stdio.h>
#include <pthread.h>

void* printNumbers(void* arg) {
    int id = *(int*)arg;
    for (int i = id * 5 + 1; i <= id * 5 + 5; i++) {
        printf("Thread %d prints %d\n", id, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, printNumbers, &ids[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}