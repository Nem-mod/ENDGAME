#include "../inc/level_point.h"

t_level_point* mx_create_lp() {
    t_level_point* point = malloc(sizeof(*point));
    point->active = false;
    point->rect.h = 50;
    point->rect.w = 50;
    point->rect.x = rand() % 900 / 2;
    point->rect.y = rand() % 1200 / 2;
    point->room = ENEMY;
    point->next = NULL;
    point->img_path = "../resource/img/point.png";
    return point;
}

void mx_render_lp(t_level_point* lp) {
    lp->tex = mx_init_texture(lp->img_path);
    SDL_RenderCopy(w_render, lp->tex, &lp->rect, NULL);
}
