#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int ascii_sum[3];
void* calculate_ascii_sum(void* arg) {
    char* name = (char*)arg;
    int sum = 0;

    for (int i = 0; i < strlen(name); i++) {
        sum += name[i];
    }
    int* result = (int*)malloc(sizeof(int));
    *result = sum;
    pthread_exit(result);
}

void* compare_sums(void* arg) {
    if (ascii_sum[0] == ascii_sum[1] && ascii_sum[1] == ascii_sum[2]) {
        printf("Youreka\n");
    } else if (ascii_sum[0] == ascii_sum[1] || ascii_sum[1] == ascii_sum[2] || ascii_sum[0] == ascii_sum[2]) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4]; 
    char* usernames[3] = {"Jamal", "Hakim", "Noor"};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, calculate_ascii_sum, usernames[i]);
    }

    for (int i = 0; i < 3; i++) {
        int* result;
        pthread_join(threads[i], (void**)&result);
        ascii_sum[i] = *result;
        free(result);  
    }

    pthread_create(&threads[3], NULL, compare_sums, NULL);
    pthread_join(threads[3], NULL);  

    return 0;
}