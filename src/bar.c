#include "../inc/bar.h"

t_bar *mx_create_bar(SDL_Window *win, SDL_Renderer *rend, t_bar_type type, SDL_Rect *base) {
    t_bar *bar = malloc(sizeof(*bar));
    int bar_shift_x = 0;
    int bar_shift_y = 0;

    switch(type) {
        case HEALTH:
            bar->bar_path = "resource/img/red.png";
            bar_shift_x = base->x + base->w / 2 - BAR_WIDTH / 2;
            bar_shift_y = base->y - 20;
            break;
        case SHIELD:
            bar_shift_x = base->x + base->w / 2 - BAR_WIDTH / 2;
            bar_shift_y = base->y - 40;
            bar->bar_path = "resource/img/blue.png";
            break;
    }
    bar->square_path = "resource/img/bar_border.png";

    bar->square_rect.x = bar_shift_x;
    bar->square_rect.y = bar_shift_y;
    bar->square_rect.h = BAR_HEIGHT;
    bar->square_rect.w = BAR_WIDTH;
    bar->square_texture = mx_init_texture(bar->square_path, win, rend);

    bar->bar_rect.x = bar_shift_x;
    bar->bar_rect.y = bar_shift_y;
    bar->bar_rect.h = BAR_HEIGHT;
    bar->bar_rect.w = BAR_WIDTH;
    bar->percent = 100;
    bar->bar_texture = mx_init_texture(bar->bar_path, win, rend);

    return bar;
}

void mx_render_bar(t_bar *bar, SDL_Renderer *rend) {
    printf("%d\n", bar->percent);
    SDL_RenderCopy(rend, bar->bar_texture, NULL, &bar->bar_rect);
    SDL_RenderCopy(rend, bar->square_texture, NULL, &bar->square_rect);
}

void mx_change_bar(t_bar *bar, int new_percent) {
    bar->percent = new_percent;
    bar->bar_rect.w = mx_percent_from_int(BAR_WIDTH, new_percent);
}

void mx_clear_bar(t_bar *bar) {
    SDL_DestroyTexture(bar->bar_texture);
    SDL_DestroyTexture(bar->square_texture);
    free(bar);
    bar = NULL;
}
