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
    
}               t_enemy;

t_enemy mx_create_enemy();
void mx_render_enemy(t_enemy *enemy);
void mx_clear_enemy(t_enemy *enemy);

#endif
