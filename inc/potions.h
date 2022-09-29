#ifndef POTIONS_H
#define POTIONS_H

#include "window_sdl.h"
#include "character.h"

#define MAX_AMOUNT_OF_PT 3
typedef enum e_potion_type {
    HEAL
}            t_potion_type;

typedef struct s_potion {
    int value;
    char* img_path;
    t_potion_type type;
    SDL_Rect rect;
    SDL_Texture *tex;
}               t_potion;

typedef struct s_potion_bar {
    char* img_path;
    t_potion* potions[MAX_AMOUNT_OF_PT];
    int potions_count;
    SDL_Rect rect;
    SDL_Texture *tex;
}               t_potion_bar;

t_potion* mx_create_potion(SDL_Window* win, SDL_Renderer* renderer);
void mx_clear_potion(t_potion* potion);

t_potion_bar* mx_create_potion_bar(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_potion_bar(t_potion_bar* potions_bar, SDL_Renderer *renderer);
void mx_clear_potion_bar(t_potion_bar* potions_bar);

void mx_handle_potion(t_potion_bar *potions_bar, t_character *player);

#endif
