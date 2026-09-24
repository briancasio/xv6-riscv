#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "Usage: time <command> [args...]\n");
    exit(1);
  }

  int start = uptime();

  int pid = fork();
  if(pid < 0){
    fprintf(2, "time: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child: execute the command
    exec(argv[1], argv + 1);
    fprintf(2, "time: exec %s failed\n", argv[1]);
    exit(1);
  }

  // Parent: wait for child and get rusage
  struct rusage ru;
  wait2(0, &ru);

  int end = uptime();
  int elapsed = end - start;
  int cputime = ru.cputime;
  int pct = (elapsed > 0) ? (cputime * 100) / elapsed : 0;

  fprintf(1, "elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n",
          elapsed, cputime, pct);
  exit(0);
}
