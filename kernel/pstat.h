#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

#ifndef _PROCSTATE_
#define _PROCSTATE_
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
#endif

struct rusage {
  uint cputime;
};

struct pstat {
  int pid;              // Process ID
  enum procstate state; // Process state
  uint64 size;          // Size of process memory (bytes)
  int ppid;             // Parent process ID
  int priority;         // Process priority (0-49)
  int eff_priority;     // Effective priority (aging) when RUNNABLE
  uint64 readytime;     // Time when process became RUNNABLE (ticks)
  uint cputime;         // CPU time used (ticks)
  char name[16];        // Parent command name
};

#endif

