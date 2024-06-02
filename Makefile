CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = simulator.o object.o

all: first second third forth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

third.o: scenarios/third.cpp
	$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp
	$(CC) $(CFLAGS) -c scenarios/forth.cpp

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp

clean:
	rm -f *.o *.exe first second third forth