#include "../inc/window_sdl.h"
#include "SDL2/SDL_image.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow("Our game!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       840, 840, 0);
    if (!win)
    {
        mx_destroy("error creating window\n");
    }
    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    w_render = rend;
    if (!w_render)
    {
      mx_destroy("error creating renderer\n");
    }

    // load the image into memory using SDL_image library function
    
    // clear the window

    SDL_RenderClear(w_render);

    SDL_Texture* tex = mx_init_texture("resource/img/map.png");
    SDL_Rect rect;
    rect.h = 850;
    rect.w = 850;
    rect.x = 100;
    rect.y = -100;
    // draw the image to the window
    SDL_RenderCopy(w_render, tex, &rect, NULL);
    SDL_RenderPresent(w_render);

    tex = mx_init_texture("resource/img/second.png");



    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT){
            // clean up resources before exiting
            SDL_DestroyTexture(tex);
            mx_destroy("error creating texture");
        }
    }
    return 0;
}
