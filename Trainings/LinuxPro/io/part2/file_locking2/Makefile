include ../../../Makefile.inc

P=io/part2/file_locking2/

all: locker non_locker

locker: locker.c common.h common.o
	@gcc -w -Wall locker.c common.o -o locker ${ECHO}locker.c

non_locker: non_locker.c common.h common.o
	@gcc -w -Wall non_locker.c common.o -o non_locker ${ECHO}non_locker.c

common.o: common.c common.h
	@gcc -w -Wall -c common.c -o common.o ${ECHO}common.c

clean:
	@${RM} *~ locker non_locker
