#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>

struct my_msg {
    long int type;
    char txt[6];
};

int main() {
    int msg_id;
    pid_t pid_otp, pid_mail;
    struct my_msg msg_queue;

    // Create a fixed key instead of using ftok
    key_t key = 1234;

    // Create message queue
    if ((msg_id = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Input workspace name
    printf("Please enter the workspace name:\n");
    char workspace[6];
    scanf("%5s", workspace);  // Restrict to avoid buffer overflow
    
    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        return 1;
    }

    // Write workspace name to the message queue
    msg_queue.type = 1;
    strncpy(msg_queue.txt, workspace, 5);  // Use strncpy to prevent overflow
    msg_queue.txt[5] = '\0';  // Ensure null-terminated string

    if (msgsnd(msg_id, &msg_queue, sizeof(msg_queue.txt), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Workspace name sent to OTP generator from log in: %s\n", workspace);
    
    // Fork for OTP generator
    pid_otp = fork();
    
    if (pid_otp == 0) {
        // OTP generator process
        if (msgrcv(msg_id, &msg_queue, sizeof(msg_queue.txt), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("OTP generator received workspace name from log in: %s\n", msg_queue.txt);
        
        // Generate OTP
        pid_t otp = getpid();
        msg_queue.type = 2;
        snprintf(msg_queue.txt, sizeof(msg_queue.txt), "%d", otp);

        if (msgsnd(msg_id, &msg_queue, sizeof(msg_queue.txt), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        printf("OTP sent to log in from OTP generator: %d\n", otp);

        // Fork for Mail process
        pid_mail = fork();
        if (pid_mail == 0) {
            // Mail process
            if (msgrcv(msg_id, &msg_queue, sizeof(msg_queue.txt), 2, 0) == -1) {
                perror("msgrcv failed");
                exit(EXIT_FAILURE);
            }
            printf("Mail received OTP from OTP generator: %s\n", msg_queue.txt);
            msg_queue.type = 3;

            if (msgsnd(msg_id, &msg_queue, sizeof(msg_queue.txt), 0) == -1) {
                perror("msgsnd failed");
                exit(EXIT_FAILURE);
            }

            printf("OTP sent to log in from mail: %s\n", msg_queue.txt);
            exit(0);
        } else {
            wait(NULL);  // Wait for mail process
        }
        exit(0);
    } else {
        wait(NULL);  // Wait for OTP generator
        
        // Read OTP from OTP generator
        if (msgrcv(msg_id, &msg_queue, sizeof(msg_queue.txt), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        char otp_from_otp[6];
        strncpy(otp_from_otp, msg_queue.txt, 6);
        otp_from_otp[5] = '\0';
        printf("Log in received OTP from OTP generator: %s\n", otp_from_otp);
        
        // Read OTP from mail
        if (msgrcv(msg_id, &msg_queue, sizeof(msg_queue.txt), 3, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        char otp_from_mail[6];
        strncpy(otp_from_mail, msg_queue.txt, 6);
        otp_from_mail[5] = '\0';
        printf("Log in received OTP from mail: %s\n", otp_from_mail);

        // Compare OTPs
        if (strcmp(otp_from_otp, otp_from_mail) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        // Remove message queue
        if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
