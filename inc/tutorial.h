#ifndef TUTORIAL_H
#define TUTORIAL_H
#include "window_sdl.h"
#define SLIDES 5

typedef struct s_tutorial {
    SDL_Rect rect; 
    SDL_Texture *textures[SLIDES];
    int slide;
}               t_tutorial;

t_tutorial* mx_create_tutorial(SDL_Window* win, SDL_Renderer* renderer);
t_scenes mx_render_tutorial(t_tutorial *tutorial, SDL_Renderer *renderer);
void mx_clear_tutorial(t_tutorial *tutorial);

#endif
