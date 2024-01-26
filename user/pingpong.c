#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int pid;
	int p[2];
	int _p[2];
	pipe(p);
	pipe(_p);
	pid = fork();
	
	//close(0);
	//close(1);
	if (pid > 0) 
	{//if the seq of parent and child matter?
	 //no, if the sync op is correct.
		char pch = 'a';
		write(p[1], &pch, 1);
		
		//close(p[1]);

		//int cid;
		wait((int *) 0);
	
		int rd = read(p[0], &pch, 1);
	//	rd = read(p[0], &pch, 1);
		if (rd == 1)
		{
			printf("%d: received pong\n", getpid());
		}
		else if (rd == 0)
		{
			printf("%d: pipe closed by child\n");
		}
		else
		{
			fprintf(2, "parent %d: read error", getpid());
		}
	}else	if (pid == 0) {
		char ch = 0;
	//	close(0);
		int crd = read(p[0], &ch, 1);
		
		if (crd == 1)
		{
			//char cch = 'b';
			printf("%d: received ping\n", getpid());
			write(p[1], &ch, 1);
		}
		else
		{
			printf("child %d: read error\n", getpid());
		}
	}
	else
	{
		fprintf(2, "fork error");
	}
	exit(0);
}
