CFLAGS := `sdl2-config --libs --cflags` --std=c11 -Wall -Wextra -Wpedantic -lSDL2_image -lSDL2_mixer -lm
LANG = clang

PROJ_NAME = ENDGAME
EXEC_NAME = endgame

.PHONY: all clean uninstall reinstall

all: $(PROJ_NAME) clean

$(PROJ_NAME):
	mkdir -p ./obj
	mkdir -p ./temp
	cp ./inc/* ./temp/
	cp ./src/* ./temp/
	$(LANG) $(CFLAGS) ./temp/*.c -include ./temp/*.h -c
	rm -rf ./temp
	mv *.o ./obj
	$(LANG) ./obj/* $(SDL) -o $(EXEC_NAME) $(CFLAGS)
	rm -rf ./obj

uninstall:
	rm -rf ./obj $(EXEC_NAME)
	
clean:
	rm -rf ./obj

reinstall: uninstall $(PROJ_NAME)

