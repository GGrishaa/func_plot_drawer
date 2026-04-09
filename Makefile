CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-lm

all: graph

graph: graph.o point.o io.o stack.o
	$(CC) $(LDFLAGS) $^ -o $@
	clear

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $< -o $@

io.o: io.c io.h point.h stack.h
	$(CC) $(CFLAGS) -c $< -o $@

point.o: point.c point.h
	$(CC) $(CFLAGS) -c $< -o $@

graph.o: graph.c point.h
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

clean:
	rm -rf *.o
	clear
