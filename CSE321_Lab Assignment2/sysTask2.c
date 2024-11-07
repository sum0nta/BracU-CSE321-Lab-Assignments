#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); 

    if (pid1 == 0) { 
        pid2 = fork();

        if (pid2 == 0) {  
            printf("I am grandchild\n");
        } else {
            wait(NULL);  
            printf("I am child\n");
        }
    } else {
        wait(NULL);  
        printf("I am parent\n");
    }

    return 0;
}
