// to write complex concurrent program,
// you should consider about the target sync behavior
// of child and parent clearly.
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int lockp[2];
//if the pipe is piped before fork,
//the fd can be transfered inter-function.

void prime_pipeline(int * p, int N) {
	char ch;
	read(lockp[0], &ch, 1);

	int head, temp = 0;
	
	read(p[0], &head, 4);
	
	printf("prime %d\n", head);
	int right_max = head;
	if (head >= N) return;
	while (temp < N) {// what to do if N is not prime?
		read(p[0], &temp, 4);
		//printf("get temp %d\n", temp);
		if (temp % head != 0) {
			right_max = temp;
			//printf("head: %d, send: %d\n", head, temp);
			write(p[1], &temp, 4);
		}
	}
	write(lockp[1], &ch, 1);
	int ppid = fork();
	if (ppid == 0) {
		if (N % head == 0) N = right_max;
		prime_pipeline(p, N);
	} else if (ppid > 0) {
		wait((int *) 0);
	} else {
		printf("fork error\n");
	}
}
int main()
{
	int p[2];
	pipe(p);
	pipe(lockp);
	int N = 35;
	int pid = fork();


	if (pid > 0) {
		char ch = 'a';
		
		for (int i = 2; i <= N; ++i) {
			//printf("send %d\n", i);
			write(p[1], &i, 4);
		}
		write(lockp[1], &ch, 1);
		//every process send all the data before 
		//the child reading, so the single pipe
		//can be easily mutiplexing.
		wait((int *) 0);//every time remember wait.
	} else if (pid == 0) {
		//which point to create right child?
		//		int head, temp = 0;
//		
//	
//		read(p[0], &head, 4);
//		printf("get head %d\n", head);
//		
//		while (temp < N) {
//			read(p[0], &temp, 4);
//			printf("get temp %d\n", temp);
//			if (temp % head != 0) {
//				write(p[1], &temp, 4);
//			}
//		}

		prime_pipeline(p, N);
	} else {
		printf("fork error\n");
	}

	exit(0);
}
