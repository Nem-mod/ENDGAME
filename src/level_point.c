#include "../inc/level_point.h"

t_level_point* mx_create_lp(SDL_Window* win, SDL_Renderer* renderer) {
    t_level_point* point = malloc(sizeof(*point));
    point->active = false;
    point->rect.h = 60;
    point->rect.w = 60;
    point->rect.x = 400 + rand() % 400;
    point->rect.y = 900 - rand() % 40 - 150;
    point->room = ENEMY;
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
