#include "../inc/menu.h"

t_menu mx_create_menu(SDL_Window* win, SDL_Renderer* renderer) {
    t_menu menu;
    menu.active = true;
    menu.rect.h = WINDOW_HEIGHT;
    menu.rect.w = WINDOW_WIDTH;
    menu.rect.x = (WINDOW_WIDTH - menu.rect.w) / 2 ;
    menu.rect.y = (WINDOW_HEIGHT - menu.rect.h) / 2;
    menu.img_path = "resource/img/menu-background.jpg";
    menu.tex = mx_init_texture(menu.img_path, win, renderer);
    menu.button_start = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2 - 150, "resource/img/button-start.png");
    menu.button_start.tex = mx_init_texture(menu.button_start.img_path, win, renderer);
    menu.button_exit = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2, "resource/img/button-exit.png");
    menu.button_exit.tex = mx_init_texture(menu.button_exit.img_path, win, renderer);
    return menu;

}
void mx_render_menu(t_menu *menu, SDL_Renderer *renderer) {
    // draw the image to the window
    SDL_RenderCopy(renderer, menu->tex, NULL,  &menu->rect);
    SDL_RenderCopy(renderer, menu->button_start.tex, NULL,  &menu->button_start.d_rect);
    SDL_RenderCopy(renderer, menu->button_exit.tex, NULL,  &menu->button_exit.d_rect);
}
int mx_handle_menu(t_menu *menu, SDL_Renderer *renderer) {
    
    if(mx_handle_button(menu->button_start.d_rect)){
        menu->img_path = "resource/img/floppa.png";
        mx_clear_menu(menu);
        SDL_RenderClear(renderer);
        return 1;
    } else if(mx_handle_button(menu->button_exit.d_rect)) {
        mx_clear_menu(menu);
        SDL_RenderClear(renderer);
        return 3;
    } 
    else {
        menu->img_path = "resource/img/menu.png";
    }
    return 0;
}

void mx_clear_menu(t_menu *menu){
    SDL_DestroyTexture(menu->tex);
}
