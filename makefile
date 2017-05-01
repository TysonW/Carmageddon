

# The compiler to use is for C++
CC=g++

# The compiler options are (all warnings)
CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

# The linker options are (all warnings)
LDFLAGS=-Wall `pkg-config --libs opencv` -std=c++11 -lpigpio -lrt -lpthread


all: Car

Car: Main.o 
	$(CC) $(LDFLAGS) Main.o -o Car

Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp

clean:
	rm *o Car
