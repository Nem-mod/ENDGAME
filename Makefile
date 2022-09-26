flags := `pkg-config --libs --cflags sdl2` -std=c11 -Wall -Wextra -Werror -Wpedantic
name := endgame

all: $(name)

$(name):
	rm -rf $(name)
	clang $(flags) -Iinc -o $(name) src/*.c

clean:
	rm -rf $(name)

uninstall:
	rm -rf $(name)

reinstall:
	make uninstall
	make
