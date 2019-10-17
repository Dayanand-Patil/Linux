DIRS=part1  part2  part3  part4

all:    
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done

clean:
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
