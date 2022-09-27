#ifndef MENU_H
#define MENU_H

#include "window_sdl.h"
#include "stdbool.h"
typedef struct s_menu {
    SDL_Rect rect; 
    char* img_path;
    bool active; 
    SDL_Texture *tex;
    
}               t_menu;

t_menu mx_create_menu();
void mx_render_menu(t_menu *menu, SDL_Renderer *renderer);
int mx_handle_menu(t_menu *menu);
void mx_clear_menu(t_menu *menu);

#endif
