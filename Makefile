CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp


clean:
	rm -f *.o first