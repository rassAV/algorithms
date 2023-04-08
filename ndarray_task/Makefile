CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
SOURCES = main.cpp

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif



all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

run: all
	$(TARGET)

clean:
	$(RM) $(TARGET)
	$(RM) *.o
