#ifndef BUTTON_H
#define BUTTON_H

#include "window_sdl.h"
typedef struct s_button {
    SDL_Rect img_rect;
    SDL_Rect d_rect;
    char* img_path;
    SDL_Texture *tex;
}              t_button;


t_button mx_create_button(int w, int h, int x, int y, char* img_path);
bool mx_handle_button(SDL_Rect rect);
bool mx_cursor_on_button(SDL_Rect rect);
#endif
