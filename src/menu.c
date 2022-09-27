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
void mx_render_menu(t_menu *menu) {
    menu->tex = mx_init_texture(menu->img_path);
    // draw the image to the window
    SDL_Rect prect;
    prect.h = 370;
    prect.w = 380;
    prect.x = 0;
    prect.y = 0;
    SDL_RenderCopy(w_render, menu->tex, &prect,  &menu->rect);
}
void mx_clear_menu(t_menu *menu){
    SDL_DestroyTexture(menu->tex);
}
