#include "../inc/window_sdl.h"
#include "../inc/map.h"
#include "../inc/menu.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow("Our game!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       300 * 4, 300 * 3, 0);
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
    
    t_map map = mx_create_map();
    mx_render_map(&map);
    SDL_RenderPresent(w_render);

    t_menu menu = mx_create_menu();
    mx_render_menu(&menu);


    SDL_RenderPresent(w_render);
    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
       
        if (event.type == SDL_QUIT){
            // clean up resources before exiting
            // SDL_DestroyTexture(tex);
            mx_clear_map(&map);
            mx_destroy("error creating texture");
        }
    }
    return 0;
}
