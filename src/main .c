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
                                       640, 640, 0);
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

    SDL_Texture* tex = mx_init_texture("resource/img/floppa.png");

    // draw the image to the window
    SDL_RenderCopy(w_render, tex, NULL, NULL);
    SDL_RenderPresent(w_render);

    tex = mx_init_texture("resource/img/second.png");

    SDL_Rect rect;
    rect.h = 50;
    rect.w = 50;
    rect.x = 0;
    rect.y = 0;

    SDL_RenderCopy(w_render, tex, NULL, &rect);
    SDL_RenderPresent(w_render);
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
