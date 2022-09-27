#include "../inc/window_sdl.h"

void mx_destroy(char* ms) {
    printf("%s\n", ms);
    printf("%s\n", SDL_GetError());
    SDL_DestroyRenderer(w_render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(-1);
}
