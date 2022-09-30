#include "../inc/menu.h"

t_menu mx_create_menu(SDL_Window* win, SDL_Renderer* renderer, int type) {
    t_menu menu;
    menu.active = true;
    menu.rect.h = WINDOW_HEIGHT;
    menu.rect.w = WINDOW_WIDTH;
    menu.rect.x = (WINDOW_WIDTH - menu.rect.w) / 2 ;
    menu.rect.y = (WINDOW_HEIGHT - menu.rect.h) / 2;
    menu.img_path = "resource/img/menu-background.jpg";
    menu.tex = mx_init_texture(menu.img_path, win, renderer);
    if(type == 1) {
        menu.buttons[0] = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2 - 300, "resource/img/button-start.png");
        menu.buttons[1] = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2 - 150, "resource/img/tuto.png");
        menu.buttons[2] = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2, "resource/img/button-exit.png");
        menu.count_of_buttons = 3;

    } else {
        menu.buttons[0] = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2 - 150, "resource/img/button-resume.png");
        menu.buttons[1] = mx_create_button(480, 110, (WINDOW_WIDTH - 480) / 2,  (WINDOW_HEIGHT) / 2, "resource/img/button-exit.png");
        menu.count_of_buttons = 2;
    }   
    
    for (int i = 0; i < menu.count_of_buttons; i++) {
        menu.buttons[i].tex = mx_init_texture(menu.buttons[i].img_path, win, renderer);
    }
    
    return menu;

}
void mx_render_menu(t_menu *menu, SDL_Renderer *renderer) {
    // draw the image to the window
    SDL_RenderCopy(renderer, menu->tex, NULL,  &menu->rect);
    for (int i = 0; i < menu->count_of_buttons; i++) {
        SDL_RenderCopy(renderer, menu->buttons[i].tex, NULL,  &menu->buttons[i].d_rect);
    }
}
int mx_handle_menu(t_menu *menu, SDL_Renderer *renderer, int type) {
    if(type == 1) {
        
        if(mx_handle_button(menu->buttons[0].d_rect)){
            SDL_RenderClear(renderer);
            return MAP;
            
        } else if(mx_handle_button(menu->buttons[1].d_rect)) {
            SDL_RenderClear(renderer);
            return TUTORIAL;
        } else if(mx_handle_button(menu->buttons[2].d_rect)) {
            mx_clear_menu(menu);
            SDL_RenderClear(renderer);
            return EXIT;
        } 
        else {
            menu->img_path = "resource/img/menu.png";
        }
    } else if (type == 2) {
        if(mx_handle_button(menu->buttons[0].d_rect)){
            mx_clear_menu(menu);
            SDL_RenderClear(renderer);
            return CLOSE_MENU;
        
        } else if(mx_handle_button(menu->buttons[1].d_rect)) {
            mx_clear_menu(menu);
            SDL_RenderClear(renderer);
            return EXIT;
        } 
    }
    
    return 0;
}

void mx_clear_menu(t_menu *menu){
    SDL_DestroyTexture(menu->tex);
    for (int i = 0; i < menu->count_of_buttons; i++) {
        SDL_DestroyTexture(menu->buttons[i].tex);
    }
}
