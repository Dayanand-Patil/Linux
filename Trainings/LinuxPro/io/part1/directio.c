/*
 *      Example for direct IO
 *      Author: Team Veda
 *      linux-2.6.25-i386
 *      version: 1.0
 *     
 */      


#define _GNU_SOURCE
#define SECTOR_SIZE 512

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main ()
{
    void  *buf;
    int fdin, fdout, rcr, rcw;
/* default chunk = 1 page */
    int size = getpagesize ();
    /* open input file, must exist */
    //fdin = open("Read.txt", O_RDONLY);
	fdin=open("Read.txt",O_DIRECT|O_RDWR|O_CREAT|O_TRUNC,0766);
	printf("%d\n",fdin);
    /* open output file, create or truncate */
    //fdout = open ("Write.txt", O_DIRECT | O_RDWR | O_CREAT | O_TRUNC, 0666);
    /* use sector aligned memory region */
    posix_memalign (&buf, size, size*8);

    while ((rcr = read (fdin, buf, size*8)) > 0) {
        rcw = write (fdin, buf, rcr);
        printf ("in = %d, out = %d\n", rcr, rcw);
        if (rcr != rcw)
            printf ("BAD values -- not sector aligned perhaps\n");
    }
    close (fdin);
    close (fdout);
    exit (0);
}
