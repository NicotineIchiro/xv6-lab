#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
//	unsigned int i = 0x00646c72;
//	printf("H%x Wo%s", 2746, &i);//%x will not do the ASCII map
//																//and %s treat the arg as a pointer,
//																//doing map from arg as begin addr,
//																//so the variable should '&'
//	int j = 10;
	printf("x=%d y=%d", 3);

	exit(0);
}
