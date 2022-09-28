#pragma once

#include "window_sdl.h"
#include "gamemath.h"
#include <stdbool.h>

#define DMG_DISP_PERCENT (10)
#define SHIELD_DMG_ABSORB_PERCENT (50)

typedef struct   s_character {
    char *character_path;
    
    SDL_Rect character_rect;

    SDL_Texture *character_texture;

    int max_hp;
    int current_hp;
    int attack;
    int crit_chance;
    int crit_dmg;
    int dodge_chance;
    int shield;
}               t_character;

t_character *mx_create_character(char *texture_path,
                                int max_hp, int attack,
                                int crit_chance, int crit_dmg,
                                int dodge_chance, int shield,
                                SDL_Window *win, SDL_Renderer *rend);
void mx_set_character(t_character *c,
                    int max_hp, int attack,
                    int crit_chance, int crit_dmg,
                    int dodge_chance, int shield);
void mx_clear_character(t_character *character);
int mx_calculate_attack(t_character *from, t_character *to);
