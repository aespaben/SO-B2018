CC = gcc
CFLAGS = -Wall -g

all: server.out client1.out client2.out client3.out client4.out


server.o: server.c
	$(CC) $(CFLAGS) -c $^

server.out: server.o
	$(CC) $^ -o $@ -pthread


client1.o: client1.c
	$(CC) $(CFLAGS) -c $^

client1.out: client1.o
	$(CC) $^ -o $@ -lm -pthread


client2.o: client2.c
	$(CC) $(CFLAGS) -c $^

client2.out: client2.o
	$(CC) $^ -o $@ -lm -pthread


client3.o: client3.c
	$(CC) $(CFLAGS) -c $^

client3.out: client3.o
	$(CC) $^ -o $@ -lm -pthread


client4.o: client4.c
	$(CC) $(CFLAGS) -c $^

client4.out: client4.o
	$(CC) $^ -o $@ -lm -pthread


.PHONY: clean

clean:
	rm -f *.out *.o *~