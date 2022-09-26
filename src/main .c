#include "../inc/window_sdl.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* win = SDL_CreateWindow("Hello, CS50!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 640, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
    }

    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT){
            // clean up resources before exiting
            SDL_DestroyWindow(win);
            SDL_Quit();
        }
    }
    
    
   
    return 0;
}
