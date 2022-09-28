#ifndef ENEMY_H
#define ENEMY_H

#include "window_sdl.h"
#include "stdbool.h"

typedef struct s_enemy {
    SDL_Rect erect; 
    char* img_path;
    bool active; 
    SDL_Texture *tex;
    int hp;
    int attack;
    bool state;
}               t_enemy;

t_enemy mx_create_enemy(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_enemy(t_enemy *enemy, SDL_Renderer *renderer);
void mx_clear_enemy(t_enemy *enemy);

#endif
