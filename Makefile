NAME = snake
EXE = $(NAME).exe
TARGET = ./$(EXE)

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = 

CFILES = $(wildcard *.c)
OBJECTS = $(CFILES:.c=.o)

all: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm *.o

run:
	$(TARGET)

.PHONY:
	clean run
