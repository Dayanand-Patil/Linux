include ../../Makefile.inc

P=io/part4/
all:
	${GCC} aio_read_write.c -lrt -o aio_read_write ${ECHO}aio_read_write.c
	${GCC} aio_read_write_list.c -lrt -o aio_read_write_list ${ECHO}aio_read_write_list.c
	${GCC} multi1.c -o multi1 ${ECHO}multi1.c
	${GCC} multi2.c -o multi2 ${ECHO}multi2.c
	${GCC} multi3.c -o multi3 ${ECHO}multi3.c
	${GCC} multi4.c -o multi4 ${ECHO}multi4.c
	${GCC} splice.c -o splice ${ECHO}splice.c
	${GCC} poll1.c -o poll1 ${ECHO}poll1.c
	${GCC} poll2.c -o poll2 ${ECHO}poll2.c

clean:
	${RM} *~ aio_read_write_list aio_read_write multi1 multi2 multi3 multi4 splice poll1 poll2 pone ptwo
