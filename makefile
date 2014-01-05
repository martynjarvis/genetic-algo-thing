CC=clang++
CFLAGS=-c -std=c++11 -stdlib=libc++
LDFLAGS=-stdlib=libc++ 
EXECUTABLE=run

all: run

$(EXECUTABLE): main.o population.o organism.o 
		$(CC) $(LDFLAGS) main.o population.o organism.o -o $(EXECUTABLE)

main.o: main.cpp 
		$(CC) $(CFLAGS) main.cpp

population.o: population.cpp 
		$(CC) $(CFLAGS) population.cpp

organism.o: organism.cpp
		$(CC) $(CFLAGS) organism.cpp

clean:
		rm -f *.o $(EXECUTABLE)
