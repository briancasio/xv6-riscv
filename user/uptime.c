#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 1){
    fprintf(2, "Usage: %s\n", argv[0]);
    exit(1);
  }

  int ticks = uptime();
  fprintf(1, "up %d clock ticks\n", ticks);
  exit(0);
}
