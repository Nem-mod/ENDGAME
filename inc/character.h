#pragma once

#include "window_sdl.h"
#include "gamemath.h"
#include "bar.h"
#include <stdbool.h>

#define DMG_DISP_PERCENT (10)

#define PLAYER_PATH "resource/img/floppa.jpeg"
#define ENEMY_PATH "resource/img/mob.png"

typedef struct   s_character {
    char *character_path;
    
    SDL_Rect character_rect;

    SDL_Texture *character_texture;

    t_bar *healthbar;
    t_bar *shieldbar;

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
int mx_calculate_character_attack(t_character *from, t_character *to);
void mx_render_character(t_character *character, SDL_Renderer *rend, SDL_Rect rect);
void mx_set_enemy(t_character *c);
