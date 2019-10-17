include ../../Makefile.inc

P=io/part2/

DIRS= filelock-1  file_locking2 

all:
	${GCC} flock.c -o flock ${ECHO}flock.c
	${GCC} mmap.c -o mmap ${ECHO}mmap.c
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done
clean:
	${RM} *~ flock mmap
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
