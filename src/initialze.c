#include "../inc/main.h"

t_window_sdl *mx_init_SDL2() {
    t_window_sdl *gameWindow = malloc(sizeof(*gameWindow));

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT,2,2048);
    gameWindow->bg_music = Mix_LoadMUS(gameWindow->music_path);

    gameWindow->window = SDL_CreateWindow("Our game!",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    gameWindow->renderer = SDL_CreateRenderer(gameWindow->window , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
 
    gameWindow->active = true;
    gameWindow->scene = MENU;

    Mix_PlayMusic(gameWindow->bg_music, -1);

    return gameWindow;
}

void mx_init_game(t_window_sdl *gameWindow, t_menu *menu, t_map *map, t_character *player, t_inventory *inventory, t_potion_bar *potions) {
    t_menu menu = mx_create_menu(gameWindow->window, gameWindow->renderer, 1);
    t_map map = mx_create_map(gameWindow->window, gameWindow->renderer);
    char* palyer_img = "resource/img/player/default_player.png";
    t_character *player =  mx_create_character(palyer_img, 100, 5, 20, 50, 10, 2, gameWindow->window, gameWindow->renderer);
    t_inventory *inventory = mx_create_inventory(gameWindow->window, gameWindow->renderer);
    mx_generate_start_cards(gameWindow->window, gameWindow->renderer, inventory);

    t_fightground *fightground = NULL;
    t_fightground *bossroom = NULL;
    t_room *room = NULL;

    t_potion_bar *potions = mx_create_potion_bar(gameWindow.window, gameWindow.renderer);
}
