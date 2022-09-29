#include "../inc/window_sdl.h"
#include "../inc/map.h"
#include "../inc/menu.h"
#include "../inc/fight.h"
#include "../inc/room.h"
#include "../inc/potions.h"
#include "../inc/escene.h"

int main() {
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *background = Mix_LoadMUS("resource/audio/song.mp3");
    t_window_sdl gameWindow;
    gameWindow.window = SDL_CreateWindow("Our game!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    gameWindow.renderer = SDL_CreateRenderer(gameWindow.window , -1, render_flags);
   


 
    gameWindow.active = true;
    gameWindow.scene = MENU;

    t_menu menu = mx_create_menu(gameWindow.window, gameWindow.renderer, 1);
    t_map map = mx_create_map(gameWindow.window, gameWindow.renderer);
    char* palyer_img = "resource/img/player/default_player.png";
    t_character *player =  mx_create_character(palyer_img, 100, 5, 20, 50, 10, 2, gameWindow.window, gameWindow.renderer);

    t_fightground *fightground = NULL;
    t_room *room = NULL;

    t_potion_bar *potions = mx_create_potion_bar(gameWindow.window, gameWindow.renderer);
    Mix_PlayMusic(background, -1);
    while (gameWindow.active) {
        SDL_RenderClear(gameWindow.renderer); // Каждый раз чистить экран чтоб картинки не накладывались друг на другаы
        if (gameWindow.scene == MENU) {
            mx_render_menu(&menu, gameWindow.renderer);
            gameWindow.scene = mx_handle_menu(&menu, gameWindow.renderer, 1);
        }
        else if (gameWindow.scene == MAP) {
            mx_render_map(&map, gameWindow.renderer);
            gameWindow.scene = mx_handle_map(&map, gameWindow.window, gameWindow.renderer);
            if (gameWindow.scene == LEVEL) {
                fightground = mx_create_fightground(gameWindow.window, gameWindow.renderer, player);
            }
            else if (gameWindow.scene == ROOM)
                room = mx_create_room(gameWindow.window, gameWindow.renderer, player, CHEST);
        }
        else if (gameWindow.scene == LEVEL) {
            gameWindow.scene = mx_render_fightground(gameWindow.window, gameWindow.renderer, fightground);
            mx_render_potion_bar(potions, gameWindow.renderer);
            mx_handle_potion(potions, player);
        }
        else if (gameWindow.scene == ROOM) {
            gameWindow.scene = mx_render_room(room, gameWindow.renderer, potions, gameWindow.window);
        }
        else if (gameWindow.scene == DEATH) {
            t_escene escene = mx_create_escene(gameWindow.window, gameWindow.renderer);
            mx_render_escene(&escene, gameWindow.renderer);
            SDL_RenderPresent(gameWindow.renderer);
            SDL_Delay(3000);
            mx_clear_escene(&escene);
            gameWindow.scene = RESTART;
            //break;
        }
        else if (gameWindow.scene == RESTART) {
            mx_clear_map(&map);
            mx_clear_points(&map);
            mx_clear_potion_bar(potions);
            mx_clear_character(player);
            menu = mx_create_menu(gameWindow.window, gameWindow.renderer, 1);
            map = mx_create_map(gameWindow.window, gameWindow.renderer);
            player =  mx_create_character(palyer_img, 100, 5, 20, 50, 10, 2, gameWindow.window, gameWindow.renderer);
            potions = mx_create_potion_bar(gameWindow.window, gameWindow.renderer);
            gameWindow.active = true;
            gameWindow.scene = MENU;
            continue;
        }

        if(gameWindow.menu) {
            mx_render_menu(&menu, gameWindow.renderer);
            if(mx_handle_menu(&menu, gameWindow.renderer, 2) == CLOSE_MENU) {
                gameWindow.menu = false;
            } else if(mx_handle_menu(&menu, gameWindow.renderer, 2) == EXIT) {
                gameWindow.scene = EXIT;
            }
        }

        SDL_RenderPresent(gameWindow.renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_ESCAPE && gameWindow.scene > MENU) {
                    menu = mx_create_menu(gameWindow.window, gameWindow.renderer, 2);
                    gameWindow.menu = !gameWindow.menu;
                }

            }
            if (event.type == SDL_QUIT || gameWindow.scene == EXIT){
                // clean up resources before exiting
                mx_clear_map(&map);
                mx_clear_points(&map);
                gameWindow.active = false;
            }
        }
        SDL_Delay(1000 / 24);
    }
    SDL_RenderClear(gameWindow.renderer);
    SDL_DestroyRenderer(gameWindow.renderer);
    Mix_FreeMusic(background);
   
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
