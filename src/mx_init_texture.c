#include "../inc/window_sdl.h"

SDL_Texture* mx_init_texture(char* path, SDL_Window* win, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {   
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        exit(-1);
    }

    return texture;

}
