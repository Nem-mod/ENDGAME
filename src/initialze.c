#include "../inc/main.h"

t_window_sdl *mx_init_SDL2() {
    t_window_sdl *gameWindow = malloc(sizeof(*gameWindow));

    gameWindow->bg_music = Mix_LoadMUS(gameWindow->music_path);

    gameWindow->window = SDL_CreateWindow("The legends of Horned Cave",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    gameWindow->renderer = SDL_CreateRenderer(gameWindow->window , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 
    gameWindow->active = true;
    gameWindow->scene = MENU;

    

    return gameWindow;
}

void mx_init_game(t_window_sdl *gameWindow) {
    
    t_menu menu = mx_create_menu(gameWindow->window, gameWindow->renderer, 1);
    t_tutorial *tutorial = mx_create_tutorial(gameWindow->window, gameWindow->renderer);
    t_map map = mx_create_map(gameWindow->window, gameWindow->renderer);

    char* palyer_img = "resource/img/player/default_player.png";
    t_character *player =  mx_create_character(palyer_img, 100, 5, 20, 50, 10, 2, gameWindow->window, gameWindow->renderer);
    t_inventory *inventory = mx_create_inventory(gameWindow->window, gameWindow->renderer);
    mx_generate_start_cards(gameWindow->window, gameWindow->renderer, inventory);

    t_vscene victory = mx_create_vscene(gameWindow->window, gameWindow->renderer);

    t_fightground *fightground = NULL;
    t_fightground *bossroom = NULL;
    t_room *room = NULL;
    int diff_count = 0;

    t_potion_bar *potions = mx_create_potion_bar(gameWindow->window, gameWindow->renderer);

    while (gameWindow->active) {
        SDL_RenderClear(gameWindow->renderer);
        if (gameWindow->scene == MENU) {
            tutorial->slide = 0;
            mx_render_menu(&menu, gameWindow->renderer);
            gameWindow->scene = mx_handle_menu(&menu, gameWindow->renderer, 1);
        } else if (gameWindow->scene == MAP) {
            mx_render_map(&map, gameWindow->renderer);
            gameWindow->scene = mx_handle_map(&map, gameWindow->window, gameWindow->renderer);
            if (gameWindow->scene == LEVEL) {
                fightground = mx_create_fightground(gameWindow->window, gameWindow->renderer, player, inventory, diff_count);
                diff_count++;
            } else if (gameWindow->scene == ROOM)
                room = mx_create_room(gameWindow->window, gameWindow->renderer, player, CHEST);
              else if (gameWindow->scene == BOSSFIGHT)
                bossroom = mx_create_bossroom(gameWindow->window, gameWindow->renderer, player, inventory);
        } else if (gameWindow->scene == LEVEL) {
            gameWindow->scene = mx_render_fightground(gameWindow->window, gameWindow->renderer, fightground);
            mx_render_potion_bar(potions, gameWindow->renderer);
            mx_handle_potion(potions, player);
        } else if (gameWindow->scene == ROOM) {
            gameWindow->scene = mx_render_room(room, gameWindow->renderer, potions, gameWindow->window);
        } else if (gameWindow->scene == DEATH) {
            t_escene escene = mx_create_escene(gameWindow->window, gameWindow->renderer);
            mx_render_escene(&escene, gameWindow->renderer);
            SDL_RenderPresent(gameWindow->renderer);
            SDL_Delay(3000);
            mx_clear_escene(&escene);
            gameWindow->scene = RESTART;
        } else if (gameWindow->scene == RESTART) {
            mx_clear_map(&map);
            mx_clear_points(&map);
            mx_clear_potion_bar(potions);
            mx_clear_character(player);
            mx_clear_inventory(inventory);
            menu = mx_create_menu(gameWindow->window, gameWindow->renderer, 1);
            map = mx_create_map(gameWindow->window, gameWindow->renderer);
            player =  mx_create_character(palyer_img, 100, 15, 20, 50, 10, 2, gameWindow->window, gameWindow->renderer);
            potions = mx_create_potion_bar(gameWindow->window, gameWindow->renderer);
            inventory = mx_create_inventory(gameWindow->window, gameWindow->renderer);
            mx_generate_start_cards(gameWindow->window, gameWindow->renderer, inventory);
            gameWindow->active = true;
            gameWindow->scene = MENU;
            continue;
        } else if (gameWindow->scene == BOSSFIGHT) {
            gameWindow->scene = mx_render_bossroom(gameWindow->window, gameWindow->renderer, bossroom);
            mx_render_potion_bar(potions, gameWindow->renderer);
            mx_handle_potion(potions, player);
        } else if (gameWindow->scene == VICTORY) {
            mx_render_vscene(&victory, gameWindow->renderer);
            SDL_RenderPresent(gameWindow->renderer);
            SDL_Delay(3000);
            gameWindow->scene = RESTART;
        } else if (gameWindow->scene == TUTORIAL) {
            gameWindow->scene = mx_render_tutorial(tutorial, gameWindow->renderer);
        }

        


        if(gameWindow->menu) {
            mx_render_menu(&menu, gameWindow->renderer);
            mx_render_inventory(gameWindow->renderer, inventory);
            mx_handle_inventory(inventory);
            if(mx_handle_menu(&menu, gameWindow->renderer, 2) == CLOSE_MENU) {
                gameWindow->menu = false;
            } else if(mx_handle_menu(&menu, gameWindow->renderer, 2) == EXIT) {
                gameWindow->scene = EXIT;
            }
        }

        SDL_RenderPresent(gameWindow->renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_ESCAPE && gameWindow->scene > MENU && gameWindow->scene != TUTORIAL) {
                    mx_deactivate_all_cards(inventory);
                    menu = mx_create_menu(gameWindow->window, gameWindow->renderer, 2);
                    gameWindow->menu = !gameWindow->menu;
                }

            }
            if (event.type == SDL_QUIT || gameWindow->scene == EXIT){
                // clean up resources before exiting
                mx_clear_map(&map);
                mx_clear_points(&map);
                gameWindow->active = false;
            }
        }
        SDL_Delay(1000 / 24);
    }

}
