CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic `pkg-config --cflags gl glfw3` -I./include
LDFLAGS = `pkg-config --libs gl glfw3` -lm

src = src/main.c src/gl3w.c src/triangles.c src/shaders.c src/mat4.c src/vec4.c

etib: $(src)
	${CC} ${CFLAGS} -o $@ $^ $(LDFLAGS)

.PHONY: run clean

run: etib
	./etib

clean:
	rm -rf ./etib
