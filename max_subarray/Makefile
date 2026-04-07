prepare: test.o

test:
	gcc -Wall -Werror -c skeleton.c -o skeleton.o
	gcc test.o skeleton.o -o max_subarray_test
	./max_subarray_test

test.o: test.c
	gcc -Wall -Werror -c test.c -o test.o

clean:
	rm -f *.o max_subarray_test

.PHONY: test prepare clean
