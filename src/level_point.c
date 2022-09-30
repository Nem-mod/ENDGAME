#include "../inc/level_point.h"

t_level_point* mx_create_lp(SDL_Window* win, SDL_Renderer* renderer) {
    t_level_point* point = malloc(sizeof(*point));
    point->active = false;
    point->rect.h = 60;
    point->rect.w = 60;
    point->rect.x = 850 + rand() % 50;
    point->rect.y = 1150 + rand() % 50;
    if (mx_rand(0, 4) == 0) {
        point->room = CHEST;
    }
    else {
        point->room = ENEMY;
    }
    point->next = NULL;
    point->img_path = "resource/img/point.png";
    point->tex = mx_init_texture(point->img_path, win, renderer);

    return point;
}

void mx_render_lp(t_level_point* lp, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, lp->tex, NULL, &lp->rect);
}

void mx_clear_lp(t_level_point* lp){
    SDL_DestroyTexture(lp->tex);
    free(lp);
    lp = NULL;
}
void mx_change_tex(t_level_point* lp, SDL_Window* win, SDL_Renderer* renderer ) {
    SDL_DestroyTexture(lp->tex);
    lp->tex = mx_init_texture(lp->img_path, win, renderer);
    SDL_DestroyTexture(lp->next->tex);
    lp->next->tex = mx_init_texture("resource/img/cpoint.png", win, renderer);
}
int mx_handle_point_level(t_level_point *lp, SDL_Window* win, SDL_Renderer* renderer) {
    int mouse_x;
    int mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    int return_val = 1;

    if (mouse_x > lp->rect.x &&
        mouse_x < lp->rect.x + lp->rect.h &&
        mouse_y > lp->rect.y &&
        mouse_y < lp->rect.y + lp->rect.w
        && lp->active == true
    ) {
        lp->img_path = "resource/img/wpoint.png";
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            mx_change_tex(lp, win, renderer);
            lp->next->active = true;
            
            lp->active = false;
            if (lp->room == ENEMY) {
                return_val = LEVEL;
            }
            else if (lp->room == CHEST) {
                return_val = ROOM;
            }
            else if (lp->room == BOSS) {
                return_val = BOSSFIGHT;
            }
        }
    }
    else {
        lp->img_path = "resource/img/cpoint.png";
    }
    return return_val;
}
