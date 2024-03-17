#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/riscv.h"
int fee()
{
	return 0;
}
int foo()
{

	return 5 + fee();
}
int fun(void)
{
	return foo();
}
void main()
{
	printf("%d\n", fun() + 1);

	exit(0);
}
