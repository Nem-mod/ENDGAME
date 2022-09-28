#ifndef GAME_CARD_H
#define GAME_CARD_H

#include "window_sdl.h"
#include "button.h"
typedef enum e_card_type {
    DMG,
    ARM,
    MG
}   t_card_type;
typedef struct s_game_card {
    int value;
    int cost;
    t_card_type type;
    char* img_path;
    SDL_Rect rect;
    SDL_Texture *tex;

} t_game_card;

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type);

void mx_clear_card(t_game_card *card);
#endif
