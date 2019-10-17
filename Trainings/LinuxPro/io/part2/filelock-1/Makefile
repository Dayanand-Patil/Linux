include ../../../Makefile.inc

P=io/part2/filelock-1/
all:
	${GCC} FLOCK2.c -o FLOCK2 ${ECHO}FLOCK2.c
	${GCC} PROC2.c -o PROC2 ${ECHO}PROC2.c
	${GCC} PROC41.c -o PROC41 ${ECHO}PROC41.c
	${GCC} PROC51.c -o PROC51 ${ECHO}PROC51.c
	${GCC} FLOCK1.c -o FLOCK1 ${ECHO}FLOCK1.c
	${GCC} FLOCK3.c -o FLOCK3 ${ECHO}FLOCK3.c
	${GCC} PROC1.c -o PROC1 ${ECHO}PROC1.c
	${GCC} PROC3.c -o PROC3 ${ECHO}PROC3.c
	${GCC} PROC42.c -o PROC42 ${ECHO}PROC42.c
	${GCC} PROC52.c -o PROC52 ${ECHO}PROC52.c
	${GCC} singlecopy.c -o singlecopy ${ECHO}singlecopy.c

clean:
	${RM} *~ FLOCK1 FLOCK2 FLOCK3 PROC2 PROC1 PROC3 PROC41 PROC42 PROC51 PROC52 singlecopy
