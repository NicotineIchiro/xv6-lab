//basic idea:
// cmd1 | xargs cmd2 argv
// => if cmd1 output in one line, then exec cmd2 in [argv output[cmd1]]
//    if output multiple line, exec cmd2 [argv output[cmd1][line1]], cmd2 [argv output[cmd1][line2]]...
// and the value passed by pipe are not considered in argv.
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

char ** fork_argv;
void xargs(int sub_argc, char ** sub_argv)
{
//how to let the sub-smd use the argline as input?	
//attach the argline behind sub argv?
	int pid = fork();

	if (pid == 0) {
		fork_argv = (char **)malloc((sub_argc) * sizeof(char *));
		for (int i = 0; i < sub_argc; ++i)
		{
			fork_argv[i] = (char *)malloc(strlen(sub_argv[i]));
			memmove(fork_argv[i], sub_argv[i], strlen(sub_argv[i]));

		  fork_argv[i][strlen(sub_argv[i])] = '\0';	
		}
		exec(fork_argv[0], fork_argv);
		printf("xargs: exec error\n");
	} else if (pid > 0) {
		wait((int *) 0);
	} else {
		fprintf(2, "xargs: fork error\n");
	}
	
	return;
}
char * subargv[MAXARG];
char buf[512];
int main(int argc, char * argv[])
{

	if (argc < 2) {
		printf("Usage: cmd1 [optional-args1] | xargs cmd2 [optional-args2]\n");
		exit(0);
	}
	if (argc > 31) {
		printf("xargs: exceed argc limit.\n");
		exit(0);
	}
	char ch;
	for (int i = 0; i < MAXARG; ++i) {
		subargv[i] = (char *)malloc(64);
	}
//the stack of xc6 is very tiny!
//big array should be static !

	//inital subargc is argc - 1
	for (int i = 1; i < argc; ++i) {
		memmove(subargv[i - 1], argv[i], strlen(argv[i]));
	}
	
	for (int i = 0,l = 0; read(0, &ch, 1) == 1 && i < 512; ++i) {
		if (ch != '\n' && ch != '\0') {
			buf[i] = ch;
		} else {
			buf[i] = '\0';
			// exec the sub-cmd.
			//have no enougn space then trap?
			memmove(subargv[argc - 1], buf + l, strlen(buf + l));
			subargv[argc - 1][strlen(buf + l)] = '\0';
			xargs(argc, subargv);
			l = i + 1;
		} 
	}
	//free(subargv);
	exit(0);
}
