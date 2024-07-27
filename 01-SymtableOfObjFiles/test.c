#include <stdio.h>

int gVar = 8;
static int sVar = 10;

void func(void) {
   printf("the global variable is: %d\n", gVar);
   printf("the static global variable is: %d\n", sVar);
}
