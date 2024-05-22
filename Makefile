CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

first: first.o
	$(CC) $(CFLAGS) -o first

second: second.o
	$(CC) $(CFLAGS) -o second second.o

clean:
	rm -f *.o first