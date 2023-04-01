CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif



all: main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.cpp
	$(CC) -c main.cpp

run: all
	$(TARGET)

clean:
	$(RM) $(TARGET)
	$(RM) *.o