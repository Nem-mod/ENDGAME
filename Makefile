flags := -std=c11 -Wall -Wextra -Werror -Wpedantic
conf := `pkg-config --libs --cflags sdl2`
sdl_i := 
name := endgame

usdl := -Iresource/include/SDL2 -Lresousce/lib -lSDL2main -lSDL2 -lSDL2_image
all: $(name)

$(name):
	rm -rf $(name)
	clang $(flags) $(conf)    ${usdl} -Iinc -o $(name) src/*.c

clean:
	rm -rf $(name)

uninstall:
	rm -rf $(name)

reinstall:
	make uninstall
	make