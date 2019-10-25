#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>

// int direction = PCI_DMA_TODEVICE ;
// int direction = PCI_DMA_FROMDEVICE ;
static int direction = PCI_DMA_BIDIRECTIONAL;
//int direction = PCI_DMA_NONE;

static char *kbuf;
static dma_addr_t handle;
static size_t size = (10 * PAGE_SIZE);
static struct dma_pool *mypool;
static size_t buf_size = 1024;
static size_t pool_align = 8;

static void output (char *kbuf, dma_addr_t handle, size_t size, char *string)
{
    unsigned long diff;
    diff = (unsigned long)kbuf - handle;
    pr_info ("kbuf=%12p, handle=%12p, size = %d\n", kbuf,(unsigned long *)handle, (int)size);
    pr_info ("(kbuf-handle)= %12p, %12lu, PAGE_OFFSET=%12lu, compare=%lu\n",
            (void *)diff, diff, PAGE_OFFSET, diff - PAGE_OFFSET);
    strcpy (kbuf, string);
    pr_info ("string written was, %s\n", kbuf);
}

static int __init my_init (void)
{

    /* dma_alloc_coherent method */

    pr_info ("Loading DMA allocation test module");
    pr_info ("Testing dma_alloc_coherent()..........");
    kbuf = dma_alloc_coherent (NULL, size, &handle, GFP_KERNEL); //DMA buffer available until program exists
	/* handle ==> gives physical addr for device 
	   kbuf ==> gives linear(kernel virtual) addr. of buffer */ 

    output (kbuf, handle, size, "This is the dma_alloc_coherent() string");
    dma_free_coherent (NULL, size, kbuf, handle);

    /* dma_map/unmap_single */
	
    pr_info ("Testing dma_map_single()................\n\n");
    kbuf = kmalloc (size, GFP_KERNEL);
    handle = dma_map_single (NULL, kbuf, size, direction); //singlr time use for each call
    output (kbuf, handle, size, "This is the dma_map_single() string");
    dma_unmap_single (NULL, handle, size, direction);
    kfree (kbuf);

    /* dma_pool method */

    pr_info ("Testing dma_pool_alloc()..........");
    mypool = dma_pool_create ("mypool", NULL, buf_size, pool_align, 0);
    kbuf = dma_pool_alloc (mypool, GFP_KERNEL, &handle);
    output (kbuf, handle, size, "This is the dma_pool_alloc() string");
    dma_pool_free (mypool, kbuf, handle);
    dma_pool_destroy (mypool);

    return 0;
}

/*


dma_alloc_coherent() 
works pretty well if your kernel program just need to allocate a DMA buffer and keep using it until the program exits. It ensures coherency by flushing cache before CPU (your program) or DMA controller read from the DMA buffer so you don't have to pay much attention to 'sync' CPU/cache/DMA controller before read/write to the DMA buffer. The only thing annoys me is that you need to keep track of the physical address dma_addr_t, buffer address and allocated size so you can dma_free_coherent() it properly later.

dma_map_single()/dma_unmap_single() 
are stream APIs and are supposed to have better performance than dma_alloc_coherent() in case the DMA buffer is single use for each call to DMA controller. Although I haven't seen any significant performance difference between them. And you are supposed to use dma_sync_single_for_device()/dma_sync_single_for_cpu() to assure coherency by yourself.

In some cases dma_map_single() is preferred over dma_alloc_coherent(). In one of my projects the DMA function has to take an allocated buffer (allocated by kzalloc()/kmalloc()) as parameter from the caller and map it to a DMA region. In this case I didn't have control over how and when the buffer would be allocated/free but can only map it to DMA region using dma_map_single()/dma_unmap_single().

*/

static void __exit my_exit (void)
{
    pr_info ("Module Unloading");
}

module_init (my_init);
module_exit (my_exit);

MODULE_AUTHOR ("Team Veda");
MODULE_DESCRIPTION ("DMA interface test");
MODULE_LICENSE ("GPL v2");

