#include<SDL2/SDL.h>
#include <stdio.h>

int main() {

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("%s", "error\n");
    }
    printf("%s", "init\n");
    SDL_Quit();
    return 0;
}
