CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic `pkg-config --cflags glfw3` -I./include
LDFLAGS = `pkg-config --libs gl glfw3` -lm

SOURCEDIR = ./src
SOURCES = $(wildcard $(SOURCEDIR)/*.c) main.c

all: etib

etib: $(SOURCES)
	${CC} ${CFLAGS} $^ -o $@ $(LDFLAGS)

.PHONY: clean clangd

clean:
	rm -rf ./cube

clangd: clean
	rm compile_commands.json
	bear -- make
