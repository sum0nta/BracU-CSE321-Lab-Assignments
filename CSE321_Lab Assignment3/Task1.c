#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h> 

struct shared {
int b;
char sel[100];
};

int main(){
	//pipe
	int fd[2];
	char buff[200];
	int p = pipe(fd);
	if(p==-1){
		perror("pipe");
	}

	//shared memory using struct
	int shmid, new_shmid;
	struct shared *s_d;
	shmid = shmget((key_t)101, sizeof(s_d), 0666 | IPC_CREAT);
	s_d = (struct shared *)shmat(shmid, NULL, 0);
	if (s_d == (void *)-1) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	
	//home (parent) process initializing b and sel
	(*s_d).b = 1000;
	printf("Provide Your Input From Given Options:\n");
	printf("1. Type a to Add Money\n");
	printf("2. Type w to Withdraw Money\n");
	printf("3. Type c to Check Balance\n");
	char input[100];
	scanf("%s", input);
	printf("Your selection: %s\n", input);
	strcpy((*s_d).sel, input);

	//fork
	pid_t a;
	a = fork();
	if(a<0){
		perror("fork");
	}
	
	//opr process (child)
	else if(a==0){
		close(fd[0]);
		struct shared *new_s_d;
		new_shmid = shmget((key_t)101, sizeof(new_s_d), 0666);
		new_s_d=(struct shared *)shmat(new_shmid,NULL,0);
		
		char store[100];
		int money;
		int temp;
		money = (*new_s_d).b;
		printf("%d\n",money);
		strcpy(store, (*new_s_d).sel);
		int m;
		if (strcmp(store, "a") == 0){
			printf("Enter amount to be added:\n");
			scanf("%d", &m);
			if (m>0){
				temp=money + m;
				(*new_s_d).b = temp;
				printf("Balance added successfully\n");
				printf("Updated balance after addition:\n");
				printf("%d\n", (*new_s_d).b);
				}
			else{
				printf("Adding failed, Invalid amount\n");	
				}	
		}
		
				
		else if (strcmp(store, "w") == 0){
		    printf("Enter amount to be withdrawn:\n");
		    scanf("%d", &m);
		    if (m > 0 && m <= money){
		    	money -= m;
			(*new_s_d).b = money;
			printf("Withdrawal successful\n");
			printf("Updated balance after withdrawal:\n");
			printf("%d\n", (*new_s_d).b);
		    	}	
		    else{
		    	printf("Withdrawal failed, Invalid amount\n");
		    	}
		  }
		
		
		else if (strcmp(store, "c") == 0){
		    printf("Your current balance is:\n");
		    printf("%d\n", (*new_s_d).b);
		    }
		    
		else{
		    printf("Invalid selection\n");
		      }
		
		strcpy(buff,"Thank you for using");
		write(fd[1],buff,sizeof(buff));
		close(fd[1]);

	}
	else{
		int status;
		wait(&status);
		close(fd[1]);
		read(fd[0],buff,sizeof(buff));
		printf("%s\n",buff);
		close(fd[0]);
	}

	return 0;
}
