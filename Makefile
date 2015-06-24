OBJS = HLog.o test.o
main:${OBJS}
	gcc -o main ${OBJS}
HLog.o:HLog.c
	gcc -g -o $@ -c $^
test.o:test.c
	gcc -g -o $@ -c $^

clean:
	rm -f main ${OBJS}
