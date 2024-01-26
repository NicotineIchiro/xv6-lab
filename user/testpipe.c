#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char * argv[])
{
	int pid;
	int p[2][2];
	pipe(p[0]);
	pipe(p[1]);

	pid = fork();

	if (pid > 0) {

	} else if (pid == 0) {

	} else {
		printf("fork error\n");
	}
	
	exit(0);
}
