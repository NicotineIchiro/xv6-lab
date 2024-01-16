#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc, char *argv[])
{
	int pid;
	int p[2];
	pipe(p);
	pid = fork();
	
	//close(0);
	//close(1);
	if (pid == 0)
	{
		char ch = 0;
		close(0);
		if (read(p[0], &ch, 1) == 1)
		{
			char cch = 'b';
			printf("%d: received ping\n", getpid());
			write(p[1], &cch, 1);
		}
	}
	else if (pid > 0) 
	{//if the seq of parent and child matter?
		//close(0);
		//close(1);
		char pch = 'a';
		write(p[1], &pch, 1);
		//int cid;
		wait((int *) 0);
		//printf("child%d finish\n", cid);
		if (read(p[0], &pch, 1) == 1)
		{
			printf("%d: received pong\n", getpid());
		}
		else
		{
			fprintf(2, "parent %d : read error", getpid());
		}
	}
	else
	{
		fprintf(2, "fork error");
	}

	exit(0);
}
