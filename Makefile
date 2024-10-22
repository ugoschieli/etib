CC = clang
CFLAGS = -g -Wall -Wextra `pkg-config --cflags gl glfw3` -I./include
LDFLAGS = `pkg-config --libs gl glfw3`

src = src/main.c src/gl3w.c src/triangles.c src/shaders.c

etib: $(src)
	${CC} ${CFLAGS} -o $@ $^ $(LDFLAGS)

.PHONY: run clean

run: etib
	./etib

clean:
	rm -rf ./etib
