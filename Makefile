CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic `pkg-config --cflags glfw3` -I./include
LDFLAGS = -L./libs `pkg-config --libs gl glfw3` -lm

SOURCEDIR = ./src
SOURCES = $(wildcard $(SOURCEDIR)/*.c)

all: libetib.so

examples: cube libetib.so

libetib.so: $(SOURCES)
	${CC} ${CFLAGS} -fPIC -shared $^ -o libs/$@ $(LDFLAGS)

cube: examples/cube/main.c
	${CC} ${CFLAGS} examples/cube/main.c -o examples/cube/cube ${LDFLAGS} -letib

.PHONY: run clean clangd

clean:
	rm -rf ./cube

clangd: clean
	rm compile_commands.json
	bear -- make
