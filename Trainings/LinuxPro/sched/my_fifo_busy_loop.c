#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>

/*
Run fifo-task with priority 1 in first terminal. Run fifo-task with priority 1 in the second terminal.

You will observe that the process which starts running first will print continuous output. The second process prints "Setting SCHED_FIFO and priority to 1" and then is silent.

Kill the first process and you will notice that the second process now starts printing output.

Conclusion: In the case of SCHED_FIFO, for tasks of the same priority, the currently running task has to yield before the next one can run. You may ask: why then did the second process print "Setting SCHED_FIFO and priority to 1? We'll soon see why.

*/


int main(int argc, char **argv)
{
	printf("Setting up the CPU affinity to zero\n");
	int i = 0; 
        cpu_set_t cset;
        CPU_ZERO( &cset ); //Clears set, so that it contains no CPUs
        CPU_SET( i, &cset); //add the cpu to set 

        if( sched_setaffinity( 0, sizeof(cset), &cset ) == -1 ) //  A thread's CPU affinity mask determines the set of CPUs on which it is eligible to run.
                perror("CPU Affinity...\n");

  int n = 0;
  printf("Setting SCHED_FIFO and priority to %d\n",atoi(argv[1]));
  struct sched_param param;
  param.sched_priority = atoi(argv[1]);
  sched_setscheduler(0, SCHED_FIFO, &param);
 
  while(1) {
    n++;
    if (!(n % 10000000)) {
      printf("%s FIFO Prio %d running (n=%d)\n",argv[2], atoi(argv[1]),n);
    }
  }
}

