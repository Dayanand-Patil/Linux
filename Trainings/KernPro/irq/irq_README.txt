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



