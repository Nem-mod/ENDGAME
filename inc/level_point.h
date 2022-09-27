#ifndef LEVEL_POINT_H
#define LEVEL_POINT_H

#include<stdbool.h>
#include<stdlib.h>
#include "window_sdl.h"
typedef enum e_type {
    ENEMY,
    CHEST
    // TRADER,
    // RESTPOINT
} t_type;

typedef struct s_level_point
{
    SDL_Rect rect;
    SDL_Texture *tex;
    bool active;
    t_type room;
    char* img_path;
    struct s_level_point *left;
    struct s_level_point *next;
    struct s_level_point *right;

}               t_level_point;

t_level_point* mx_create_lp(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_lp(t_level_point* lp, SDL_Renderer *renderer);
void mx_clear_lp(t_level_point* lp);
void mx_change_tex(t_level_point* lp, SDL_Window* win, SDL_Renderer* renderer );
void mx_handle_point_level(t_level_point *lp, SDL_Window* win, SDL_Renderer* renderer);

#endif
