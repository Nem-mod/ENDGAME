#include "../inc/menu.h"

t_menu mx_create_menu() {
    t_menu menu;
    menu.active = true;
    menu.rect.h = 300;
    menu.rect.w = 300;
    menu.rect.x = WINDOW_WIDTH / 2;
    menu.rect.y = WINDOW_HEIGHT / 4;
    menu.img_path = "resource/img/menu.png";
    return menu;

}
void mx_render_menu(t_menu *menu, SDL_Renderer *renderer) {
    menu->tex = mx_init_texture(menu->img_path);
    // draw the image to the window
    SDL_Rect prect;
    prect.h = 370;
    prect.w = 380;
    prect.x = 0;
    prect.y = 0;
    SDL_RenderCopy(renderer, menu->tex, &prect,  &menu->rect);
}
int mx_handle_menu(t_menu *menu) {
    int mouse_x;
    int mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (mouse_x > menu->rect.x &&
        mouse_x < menu->rect.x + menu->rect.h &&
        mouse_y > menu->rect.y &&
        mouse_y < menu->rect.y + menu->rect.w
    ) {
        menu->img_path = "resource/img/floppa.png";
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            return 1;
        }
    }
    else {
        menu->img_path = "resource/img/menu.png";
    }
    return 0;
}
void mx_clear_menu(t_menu *menu){
    SDL_DestroyTexture(menu->tex);
}
