#include "../inc/level_point.h"

t_level_point* mx_create_lp() {
    t_level_point* point = malloc(sizeof(*point));
    point->active = false;
    point->rect.h = 60;
    point->rect.w = 60;
    point->rect.x = 400 + rand() % 400;
    point->rect.y = 900 - rand() % 40 - 150;
    point->room = ENEMY;
    point->next = NULL;
    point->img_path = "resource/img/point.png";
    return point;
}

void mx_render_lp(t_level_point* lp) {
    lp->tex = mx_init_texture(lp->img_path);
    printf("%s", lp->img_path);
    SDL_RenderCopy(w_render, lp->tex, NULL, &lp->rect);
}
