IRQ: IRQs are hardware lines over which devices can send interrupt signals to the microprocessor

cat /proc/stat
cat /proc/interrupts

    what is happening after request_irq()?

A device driver registers an interrupt handler and enables a given interrupt line for handling by calling request_irq().

the call flow is :-

    request_irq() -> setup_irq() to register the struct irqaction.
    setup_irq() -> start_irq_thread() to create a kernel thread to service the interrupt line.

The thread’s work is implemented in do_irqd(). Only one thread can be created per interrupt line, and shared interrupts are still handled by a single thread.

through request_irq() use ISR(Interrupt handler) is passed to start_irq_thread(). start_irq_thread() create a kernel thread that call your ISR.



	    How a particular handler is getting called on receiving interrupt?

when an interrupt occur, PIC controller give interrupt info to cpu.

A device sends a PIC chip an interrupt, and the PIC tells the CPU an interrupt occurred (either directly or indirectly). When the CPU acknowledges the "interrupt occurred" signal, the PIC chip sends the interrupt number (between 00h and FFh, or 0 and 255 decimal) to the CPU. this interrupt number is used an index of interrupt vector table.

A processor typically maps each interrupt type to a corresponding pointer in low memory. The collection of pointers for all the interrupt types is an interrupt vector. Each pointer in the vector points to the ISR for the corresponding interrupt type (IRQ line)." An interrupt vector is only ONE memory address of one interrupt handler. An interrupt vector table is a group of several memory addresses." 


	******SoftIRQs vs Tasklets***********

/* PLEASE, avoid to allocate new softirqs, if you need not _really_ high
   frequency threaded job scheduling. For almost all the purposes
   tasklets are more than enough. F.e. all serial device BHs et
   al. should be converted to tasklets, not to softirqs.
 */

enum
{
        HI_SOFTIRQ=0,    /* High Priority */
        TIMER_SOFTIRQ,
        NET_TX_SOFTIRQ,
        NET_RX_SOFTIRQ,
        BLOCK_SOFTIRQ,
        BLOCK_IOPOLL_SOFTIRQ,
        TASKLET_SOFTIRQ,
        SCHED_SOFTIRQ,
        HRTIMER_SOFTIRQ,
        RCU_SOFTIRQ,    /* Preferable RCU should always be the last softirq */

        NR_SOFTIRQS
};

The key differences between softirq and tasklet are:

    	---> Allocation

    Softirqs are statically allocated at compile-time. Unlike tasklets, you cannot dynamically register and destroy softirqs.
    Tasklets can be statically allocated using DECLARE_TASKLET(name, func, data) or can also be allocated dynamically and initialized at runtime using tasklet_init(name, func, data)

    	---> Concurrency

    Softirqs can run concurrently on several CPUs, even if they are of the same type because softirqs are reentrant functions and must explicitly protect their data structures with spinlocks.
    Tasklets are non-reentrant and tasklets of the same type are always serialized: in other words, the same type of tasklet cannot be executed by two CPUs at the same time. However, tasklets of different types can be executed concurrently on several CPUs.

	---> Processing

    Softirqs are activated by means of the raise_softirq(). The pending softirqs are processed by do_softirq() and ksoftirqd kernel thread after being enabled by local_bh_enable() or by spin_unlock_bh()
    Tasklets are a bottom-half mechanism built on top of softirqs i.e. tasklets are represented by two softirqs: HI_SOFTIRQ and TASKLET_SOFTIRQ. Tasklets are actually run from a softirq. The only real difference in these types is that the HI_SOFTIRQ based tasklets run prior to the TASKLET_SOFTIRQ tasklets. So, tasklet_schedule() basically calls raise_softirq(TASKLET_SOFTIRQ)
    Note that softirqs (and hence tasklets and timers) are run on return from hardware interrupts, or on return from a system call. Also as soon as the thread that raised the softirq ends, that single softirq (and on other) is run to minimize softirq latency.

shareimprove this answer

