#ifndef INVENTORY_H
#define INVENTORY_H

#include "window_sdl.h"
#include "game_card.h"

#define START_AMOUNT_OF_CARDS (2)
#define MAX_CARDS (7)

typedef struct  s_inventory {
    int current_cards;
    t_game_card *cards[MAX_CARDS];

    char *inv_path;
    SDL_Rect rect;
    SDL_Texture *texture;
}               t_inventory;

void mx_create_inventory(SDL_Window *win, SDL_Renderer *rend);
void mx_generate_start_cards(SDL_Window *win, SDL_Renderer *rend, t_inventory *inv);

#endif
