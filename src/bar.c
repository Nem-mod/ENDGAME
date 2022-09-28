#include "../inc/bar.h"

t_bar *mx_create_bar(SDL_Window *win, SDL_Renderer *rend, t_bar_type type) {
    t_bar *bar = malloc(sizeof(*bar));

    switch(type) {
        case HEALTH:
            bar->bar_path = "resource/img/red.png";
            break;
        case SHIELD:
            bar->bar_path = "resource/img/blue.png";
            break;
    }
    bar->square_path = "resource/img/bar_border.png";

    bar->square_rect.x = 0;
    bar->square_rect.y = 0;
    bar->square_rect.h = BAR_HEIGHT;
    bar->square_rect.w = BAR_WIDTH;
    bar->square_texture = mx_init_texture(bar->square_path, win, rend);

    bar->bar_rect.x = 0;
    bar->bar_rect.y = 0;
    bar->bar_rect.h = BAR_HEIGHT;
    bar->bar_rect.w = BAR_WIDTH;
    bar->percent = 100;
    bar->bar_texture = mx_init_texture(bar->bar_path, win, rend);

    return bar;
}

void mx_render_bar(t_bar *bar, SDL_Renderer *rend) {
    SDL_RenderCopy(rend, bar->bar_texture, NULL, &bar->bar_rect);
    SDL_RenderCopy(rend, bar->square_texture, NULL, &bar->square_rect);
}

void mx_change_bar(t_bar *bar, int new_percent) {
    bar->percent = new_percent;
    bar->bar_rect.w = mx_percent_from_int(BAR_WIDTH, new_percent);
}

void mx_clear_bar(t_bar *bar) {
    SDL_DestroyTexture(bar->bar_texture);
    free(bar);
    bar = NULL;
}
