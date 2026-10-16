#include "kernel/types.h"
#include "user/user.h"

static void burn(long n) {
  volatile long x = 0;
  for (long i = 0; i < n; i++)
    x++;
}

int main(void) {
  if (fork() == 0) {
    setpriority(40);
    burn(500000000L);
    printf("high done\n");
    exit(0);
  }
  if (fork() == 0) {
    setpriority(0);
    burn(100000000L);
    printf("low done (aging)\n");
    exit(0);
  }
  wait(0);
  wait(0);
  exit(0);
}
