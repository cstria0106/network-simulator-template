CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

first: first.o
	$(CC) $(CFLAGS) -o first

clean:
	rm -f *.o first