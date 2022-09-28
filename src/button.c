#include "../inc/button.h"


t_button mx_create_button(int w, int h,int x, int y, char* img_path){
    t_button button;
    button.img_path = img_path;
    button.d_rect.x = x;
    button.d_rect.y = y;
    button.d_rect.w = w;
    button.d_rect.h = h;
    button.img_rect.w = w;
    button.img_rect.h = h;
    button.img_rect.x = x;
    button.img_rect.y = x;
    return button;
}

bool mx_handle_button(SDL_Rect rect){
    int mouse_x;
    int mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (mouse_x > rect.x &&
        mouse_x < rect.x + rect.w &&
        mouse_y > rect.y &&
        mouse_y < rect.y + rect.h
    ) {
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            return true;
        }
    }
    return false;
}
