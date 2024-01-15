#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(2, "Usage: sleep [time]\n");
		exit(1);
	}
	for (int i = 0, len = strlen(argv[1]); i < len; ++i)
	{
		if (argv[1][i] < '0' || '9' < argv[1][i])
		{
			fprintf(2, "Error: time should be a decimal\n");
			exit(1);
		}
	}

	sleep(atoi(argv[1]));

	exit(0);
}
