# The compiler to use is for C++
CC=g++

# The compiler options are (all warnings)
CFLAGS=-Wall `pkg-config --cflags opencv` -std=c++11 -c

# The linker options are (all warnings)
LDFLAGS=-Wall `pkg-config --libs opencv` -std=c++11 -lpigpio -lrt -lpthread

all: Car

Car: Main.o Motor.o Comm.o Track.o BufferToggle.o
	$(CC) $(LDFLAGS) Main.o Motor.o Comm.o Track.o BufferToggle.o -o Car

Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp

Motor.o: Motor.cpp
	$(CC) $(CFLAGS) Motor.cpp

Comm.o: Comm.cpp
	$(CC) $(CFLAGS) Comm.cpp

Track.o: Track.cpp
	$(CC) $(CFLAGS) Track.cpp

BufferToggle.o: BufferToggle.cpp
	$(CC) $(CFLAGS) BufferToggle.cpp

clean:
	rm *.o Car