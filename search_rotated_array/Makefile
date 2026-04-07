prepare: test.o

test:
	gcc -Wall -Werror -c skeleton.c -o skeleton.o
	gcc test.o skeleton.o -o rotated_search_test
	./rotated_search_test

test.o: test.c
	gcc -Wall -Werror -c test.c -o test.o

clean:
	rm -f *.o rotated_search_test

.PHONY: test prepare clean
