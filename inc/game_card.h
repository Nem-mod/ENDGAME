#ifndef GAME_CARD_H
#define GAME_CARD_H

#include "window_sdl.h"
#include "character.h"
#include "gamemath.h"
#include "button.h"

#define CARD_TYPE_COUNT (2)

typedef enum    e_card_type {
    DMG,
    ARM
}               t_card_type;
typedef struct  s_game_card {
    int attack;
    int defence;
    int heal;
    int cost;
    t_card_type type;
    char* img_path;
    SDL_Rect rect;
    SDL_Texture *tex;
    bool is_active;
}               t_game_card;

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type, int lvl);
void mx_activate_card(t_character *player, t_game_card *card);
int mx_calculate_card_attack(t_game_card *from, t_character *to);
t_game_card *mx_copy_card(t_game_card *src, SDL_Window *win, SDL_Renderer *rend);
void mx_clear_card(t_game_card *card);

t_game_card * mx_get_card_sword(t_game_card *card, int lvl);
t_game_card * mx_get_card_shield(t_game_card *card, int lvl);

#endif
