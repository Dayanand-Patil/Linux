#include <sched.h>
#include <stdio.h>
/*
Run other-task in Terminal 1. Run fifo-task with priority 99 in Terminal 2.

You will observe that both processes run ! A real-time process always has a higher priority than a normal process. The fifo-task with priority 99 is supposed to be the highest priority on the system. Why does the SCHED_OTHER task still get to run?

Conclusion: Something unexpected is happening. Now is the best time to explain the Linux Real-Time group Scheduling.
*/


int main(int argc, char **argv)
{
  printf("Setting SCHED_OTHER and priority to %d\n",atoi(argv[1]));
  struct sched_param param;
  param.sched_priority = atoi(argv[1]);
  sched_setscheduler(0, SCHED_OTHER, &param);
  int n = 0;
  while(1) {
    n = n + 1;
    if (!(n % 10000000)) {
      printf("%s OTHER Prio %d running (n=%d)\n",argv[2], atoi(argv[1]),n);
    }
  }
}
