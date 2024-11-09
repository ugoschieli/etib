CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic `pkg-config --cflags glfw3 freetype2` -I./include
LDFLAGS = `pkg-config --libs gl glfw3 freetype2` -lm

SOURCEDIR = ./src
SOURCES = $(wildcard $(SOURCEDIR)/*.c) main.c

all: etib

etib: $(SOURCES)
	${CC} ${CFLAGS} $^ -o $@ $(LDFLAGS)

.PHONY: clean clangd run

run: etib
	./etib

clean:
	rm -rf ./etib

clangd: clean
	rm compile_commands.json
	bear -- make
