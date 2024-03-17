#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int g(int x) {
	int gv = 2;
	printf("gv :%p\n", &gv);
  return gv % 5;
}

int f(int x) {
	int fv = g(x);
	printf("fv :%p\n", &fv);
  return fv;
}

void main(void) {
  int mainv = 1;
	printf("mainv :%p\n", &mainv);
  printf("%d %d\n", f(8)+1, 13);
  exit(0);
}
