CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic `pkg-config --cflags gl glfw3` -I../../include
LDFLAGS = `pkg-config --libs gl glfw3` -lm

SOURCEDIR = ../../src
SOURCES = $(wildcard $(SOURCEDIR)/*.c) main.c

triangles: $(SOURCES)
	${CC} ${CFLAGS} -o $@ $^ $(LDFLAGS)

.PHONY: run clean clangd

run: triangles
	./triangles

clean:
	rm -rf ./triangles

clangd: clean
	rm compile_commands.json
	bear -- make
