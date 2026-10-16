#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int prio;

  printf("=== Test Priority System Calls ===\n");

  // 1. Check initial priority
  prio = getpriority();
  printf("Initial priority: %d\n", prio);

  // 2. Test setpriority with a valid value
  printf("Setting priority to 25...\n");
  if(setpriority(25) < 0){
    printf("FAILED: setpriority(25) returned error\n");
    exit(1);
  }
  prio = getpriority();
  if(prio != 25){
    printf("FAILED: getpriority() returned %d, expected 25\n", prio);
    exit(1);
  }
  printf("SUCCESS: Current priority is %d\n", prio);

  // 3. Test invalid priorities (< 0 or > 49)
  printf("Testing invalid priority (-1): ");
  if(setpriority(-1) < 0){
    printf("correctly rejected (-1)\n");
  } else {
    printf("FAILED: allowed negative priority!\n");
  }

  printf("Testing invalid priority (50): ");
  if(setpriority(50) < 0){
    printf("correctly rejected (50)\n");
  } else {
    printf("FAILED: allowed priority > 49!\n");
  }

  // 4. Test priority inheritance with fork
  printf("Testing fork inheritance...\n");
  int pid = fork();
  if(pid < 0){
    printf("FAILED: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child process
    int cprio = getpriority();
    printf("  [Child] Inherited priority: %d (expected 25)\n", cprio);
    if(cprio != 25){
      printf("  [Child] FAILED: did not inherit parent priority\n");
      exit(1);
    }
    printf("  [Child] Changing own priority to 10...\n");
    setpriority(10);
    printf("  [Child] New priority: %d\n", getpriority());
    exit(0);
  }

  // Parent waits for child
  wait(0);

  // Verify parent priority was not modified by child
  prio = getpriority();
  printf("Parent priority after child exit: %d (should still be 25)\n", prio);

  printf("=== All priority tests passed! ===\n");
  exit(0);
}
