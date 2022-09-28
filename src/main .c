#include "../inc/window_sdl.h"
#include "../inc/map.h"
#include "../inc/menu.h"
#include "../inc/fight.h"

int main() {

    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Our game!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       300 * 4, 300 * 3, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
   


    t_window_sdl gameWindow;
    gameWindow.window = win;
    gameWindow.renderer = rend;
    gameWindow.active = true;
    gameWindow.scene = MENU;

    t_menu menu = mx_create_menu(gameWindow.window, gameWindow.renderer);
    t_map map = mx_create_map(gameWindow.window, gameWindow.renderer);
    char* palyer_img = "resource/img/player/default_player.png";
    t_character *player =  mx_create_character(palyer_img, 100, 5, 20, 50, 10, 2, win, rend);

    t_fightground *fightground = mx_create_fightground(gameWindow.window, gameWindow.renderer, player);

    while (gameWindow.active) {
        SDL_RenderClear(gameWindow.renderer); // Каждый раз чистить экран чтоб картинки не накладывались друг на другаы

        if (gameWindow.scene == MENU) {
            mx_render_menu(&menu, gameWindow.renderer);
            gameWindow.scene = mx_handle_menu(&menu, gameWindow.renderer);
            //mx_clear_menu(&menu); // Зач чистить?
        }
        else if (gameWindow.scene == MAP) {
            mx_render_map(&map, gameWindow.renderer);
            gameWindow.scene = mx_handle_map(&map, gameWindow.window, gameWindow.renderer);
            //mx_clear_map(&map);
        }
        else if (gameWindow.scene == LEVEL) {
            mx_render_fightground(fightground, gameWindow.renderer);
            mx_handle_cards(fightground);
        }
        
        SDL_RenderPresent(gameWindow.renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
        
            if (event.type == SDL_QUIT || gameWindow.scene == EXIT){
                // clean up resources before exiting
                mx_clear_map(&map);
                mx_clear_points(&map);
                gameWindow.active = false;
            }
        }
        SDL_Delay(1000 / 60);
    }
    SDL_RenderClear(gameWindow.renderer);
    SDL_DestroyRenderer(gameWindow.renderer);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
