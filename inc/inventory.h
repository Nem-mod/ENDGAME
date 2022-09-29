#ifndef INVENTORY_H
#define INVENTORY_H

#include "window_sdl.h"
#include "game_card.h"

#define START_AMOUNT_OF_CARDS (3)
#define MAX_CARDS (7)

typedef struct  s_inventory {
    int current_cards;
    t_game_card *cards[MAX_CARDS];

    char *inv_path;
    SDL_Rect rect;
    SDL_Texture *texture;
}               t_inventory;

t_inventory *mx_create_inventory(SDL_Window *win, SDL_Renderer *rend);
void mx_render_inventory(SDL_Renderer *rend, t_inventory *inv);
void mx_generate_start_cards(SDL_Window *win, SDL_Renderer *rend, t_inventory *inv);
bool mx_add_card_to_inventory(t_inventory *inv, t_game_card *src_card, SDL_Window *win, SDL_Renderer *rend);
void mx_shift_inventory_cards(t_inventory *inv);

#endif
