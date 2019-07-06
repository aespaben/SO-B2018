CC = gcc
CFLAGS = -Wall -g

all: server client1 client2 client3 client4


server.o: server.c
	$(CC) $(CFLAGS) -c $^

server: server.o
	$(CC) $^ -o $@ -pthread


client1.o: client1.c
	$(CC) $(CFLAGS) -c $^

client1: client1.o
	$(CC) $^ -o $@ -lm -pthread


client2.o: client2.c
	$(CC) $(CFLAGS) -c $^

client2: client2.o
	$(CC) $^ -o $@ -lm -pthread


client3.o: client3.c
	$(CC) $(CFLAGS) -c $^

client3: client3.o
	$(CC) $^ -o $@ -lm -pthread


client4.o: client4.c
	$(CC) $(CFLAGS) -c $^

client4: client4.o
	$(CC) $^ -o $@ -lm -pthread


.PHONY: clean

clean:
	rm -f server client1 client2 client3 client4 *.o *~