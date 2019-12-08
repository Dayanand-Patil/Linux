#include <sched.h>
#include <stdio.h>

/*
Scenario 2

Run rr-task with priority 1 in Terminal 1. Run rr-task with priority 1 in Terminal 2.

You will observer that both tasks will run continuously.

Conclusion: Tasks of the same priority when running with RR_SCHEDULING will get an equal interval run. This is the interval returned by sched_rr_get_interval().
Scenario 3

Run rr-task with priority 1 in Terminal 1. Run rr-task with priority 2 in Terminal 2.

You will observe that as long as the second instance with priority 2 is running, the first instance with priority 1 will not run.

Conclusion: Nothing surprising here. This behaviour is common to any real-time scheduled process, whether it is RR or FIFO. A higher priority will always have priority over the lower priority unless it explicitly yields.

The differences in SCHED_RR and SCHED_FIFO are only apparent when tasks have the
same priority. When the tasks have different priorities, the higher priority always
wins.

You can repeat the experiment with different combinations of rr-task and fifo-task.

*/

int main(int argc, char **argv)
{
  printf("Setting SCHED_RR and priority to %d\n",atoi(argv[1]));
  struct sched_param param;
  param.sched_priority = atoi(argv[1]);
  sched_setscheduler(0, SCHED_RR, &param);
  int n = 0;
  while(1) {
    n = n + 1;
    if (!(n % 10000000)) {
      printf("Inst:%s RR Prio %d running (n=%d)\n",argv[2], atoi(argv[1]),n);
    }
  }
}

