prepare: test.o

test:
	gcc -Wall -Werror -c skeleton.c -o skeleton.o
	gcc test.o skeleton.o -o dedup_test
	./dedup_test

test.o: test.c
	gcc -Wall -Werror -c test.c -o test.o

clean:
	rm -f *.o dedup_test

.PHONY: test prepare clean
