CC = gcc
CFLAGS = -Wall -Wextra --debug --extra --pedantic -std=c99 -MMD -MP

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
