#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int p[2];
void forkPrint(int pid)
{
	if (pid > 0) {
		char pch;
		read(p[0], &pch, 1);
		printf("parent %d: pid %d\n", pid, getpid());
		write(p[1], &pch, 1);
		wait((int *)0);
	} else if (pid == 0) {
		char cch = 'c';
		write(p[1], &cch, 1);
		read(p[0], &cch, 1);
		printf("child %d: pid %d\n", pid, getpid());
	} else {
		printf("fork error\n");
	}
}
int main(int argc, char * argv[])
{
	pipe(p);
//	forkPrint(pid);
//
	int pid = fork();
	for (int i = 0; i < 10; ++i)
		if (pid == 0) {
			pid = fork();// every time fork 
									 // note the return val.
		}
	printf("%d", getpid());
//	//forkPrint(pid);

	exit(0);
}
