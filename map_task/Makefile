CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
SOURCE = main.cpp

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif



all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

run: all
	.\$(TARGET) | py .\graphic.py

clean:
	$(RM) $(TARGET)