#include "kernel/types.h"
#include "user/user.h"

// Simple CPU burn
static void burn(int n) {
    volatile int x = 0;
    for (int i = 0; i < n; i++) x++;
}

int main(void) {
    printf("Priority scheduler test\n");
    printf("Fork low priority (0) and high priority (40)\n");

    // Low priority child
    if (fork() == 0) {
        setpriority(0);
        burn(80000000);
        printf("LOW priority (0) done\n");
        exit(0);
    }

    // High priority child
    if (fork() == 0) {
        setpriority(40);
        burn(80000000);
        printf("HIGH priority (40) done\n");
        exit(0);
    }

    wait(0);
    wait(0);
    printf("Both done. HIGH should have finished first.\n");
    exit(0);
}
