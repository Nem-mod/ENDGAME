#ifndef BAR_H
#define BAR_H

#include "window_sdl.h"
#include "gamemath.h"
#include <stdio.h>

#define BAR_WIDTH (100)
#define BAR_HEIGHT (15)

typedef enum    e_bar_type {
    HEALTH,
    SHIELD
}               t_bar_type;
typedef struct  s_bar{
    char *bar_path;
    SDL_Rect bar_rect;
    SDL_Texture *bar_texture;

    char *square_path;
    SDL_Rect square_rect;
    SDL_Texture *square_texture;

    int percent;
}               t_bar;

t_bar *mx_create_bar(SDL_Window *win, SDL_Renderer *rend, t_bar_type type, SDL_Rect *base);
void mx_render_bar(t_bar *bar, SDL_Renderer *rend);
void mx_change_bar(t_bar *bar, int new_percent);
void mx_clear_bar(t_bar *bar);

#endif
