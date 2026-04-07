prepare: test.o

test:
	gcc -Wall -Werror -c skeleton.c -o skeleton.o
	gcc test.o skeleton.o -o two_sum_test
	./two_sum_test

test.o: test.c
	gcc -Wall -Werror -c test.c -o test.o

clean:
	rm -f *.o two_sum_test

.PHONY: test prepare clean
