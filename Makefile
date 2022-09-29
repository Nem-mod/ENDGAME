flags := -std=c11 -Wall -Wextra -Werror -Wpedantic
conf := `pkg-config --libs --cflags sdl2`
sdl_i := -lSDL2_image -lSDL2_mixer
name := endgame

all: $(name)

$(name):
	rm -rf $(name)
	clang $(flags) $(conf) $(sdl_i) -Iinc -o $(name) src/*.c

clean:
	rm -rf $(name)

uninstall:
	rm -rf $(name)

reinstall:
	make uninstall
	make
