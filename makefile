CC=clang++
CFLAGS=-c -std=c++11 -stdlib=libc++
LDFLAGS=-stdlib=libc++ 
EXECUTABLE=run

all: run

$(EXECUTABLE): main.o 
		$(CC) $(LDFLAGS) main.o -o $(EXECUTABLE)

main.o: main.cpp 
		$(CC) $(CFLAGS) main.cpp

clean:
		rm -f *.o $(EXECUTABLE)
