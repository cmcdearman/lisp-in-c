CFLAGS = -std=c11 -Wall -g -Wno-parentheses -Wno-unused-const-variable
SRC    = $(wildcard src/*.c)
OBJ    = $(patsubst src/%.c, obj/%.o, $(SRC))
UNAME  = $(shell uname)

ifeq ($(OS),Windows_NT)
	BIN=lisp-in-c.exe
else
	BIN=lisp-in-c
endif

ifeq ($(UNAME), Darwin)
	CC=clang
	GDB=lldb
else
	CC=gcc
	GDB=gdb
endif

all: $(BIN)

obj:
	mkdir $@

obj/%.o: src/%.c obj
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: all
	./$(BIN)

clean:
	rm -rf $(BIN) $(OBJ)

test: clean all
	./$(BIN)

run: clean all
	./$(BIN)

debug: clean all
	$(GDB) ./$(BIN)

leak: clean all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN)

