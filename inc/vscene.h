#ifndef VSCENE_H
#define VSCENE_H

#include "window_sdl.h"
#include "stdbool.h"
typedef struct s_vscene {
    SDL_Rect rect; 
    char* img_path;
    bool active; 
    SDL_Texture *tex;

    
}               t_vscene;

t_vscene mx_create_vscene(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_vscene(t_vscene *vscene, SDL_Renderer *renderer);
void mx_clear_vscene(t_vscene *vscene);

#endif
