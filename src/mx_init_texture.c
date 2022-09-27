#include "../inc/window_sdl.h"

SDL_Texture* mx_init_texture(char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(w_render);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* texture = SDL_CreateTextureFromSurface(w_render, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {   
        mx_destroy("error creating texture\n");
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        exit(-1);
    }

    return texture;

}
