#ifndef ESCENE_H
#define ESCENE_H

#include "window_sdl.h"
#include "stdbool.h"
typedef struct s_escene {
    SDL_Rect rect; 
    char* img_path;
    bool active; 
    SDL_Texture *tex;

    
}               t_escene;

t_escene mx_create_escene(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_escene(t_escene *escene, SDL_Renderer *renderer);
void mx_clear_escene(t_escene *escene);

#endif
