CC = gcc
CFLAGS = -Wall -Wextra --debug --extra --pedantic -std=c11 -MMD -MP -lreadline

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/obj/%.o)
DEP = $(OBJ:build/obj/%.o=build/dep/%.d)

TARGET = build/main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

build/obj/%.o: src/%.c | build/obj build/deps
	$(CC) $(CFLAGS) -c $< -o $@
-include $(DEP)

build/obj:
	mkdir -p build/obj

build/deps:
	mkdir -p build/deps

run:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
