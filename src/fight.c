#include "../inc/fight.h"

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend) {
    t_fightground *fg = malloc(sizeof(*fg));

    fg->background_path = "resource/img/fight/background.jfif";
    fg->floor_path = "resource/img/fight/floor.jpg";
    fg->frontground_path = "resource/img/fight/column.png";

    fg->backg_rect.x = 0;
    fg->backg_rect.y = 0;
    fg->backg_rect.h = WINDOW_HEIGHT / 1.5;
    fg->backg_rect.w = WINDOW_WIDTH;
    fg->backg_texture = mx_init_texture(fg->background_path, win, rend);

    fg->floor_rect.x = 0;
    fg->floor_rect.y = WINDOW_HEIGHT / 1.5;
    fg->floor_rect.h = WINDOW_HEIGHT / 4;
    fg->floor_rect.w = WINDOW_WIDTH;
    fg->floor_texture = mx_init_texture(fg->floor_path, win, rend);

    fg->frontg_rect.x = 0;
    fg->frontg_rect.y = 0;
    fg->frontg_rect.h = WINDOW_HEIGHT / 1.5;
    fg->frontg_rect.w = WINDOW_WIDTH;
    fg->frontg_texture = mx_init_texture(fg->frontground_path, win, rend);


    fg->energy = 5;
    fg->cards[0] = mx_create_card(win, rend, DMG);
    fg->cards[1] = mx_create_card(win, rend, ARM);
    fg->cards[2] = mx_create_card(win, rend, MG);
    return fg;
}

void mx_render_fightground(t_fightground *fg, SDL_Renderer *rend) {
    SDL_RenderCopy(rend, fg->backg_texture, NULL, &fg->backg_rect);
    SDL_RenderCopy(rend, fg->floor_texture, NULL, &fg->floor_rect);
    SDL_RenderCopy(rend, fg->frontg_texture, NULL, &fg->frontg_rect);
}

void mx_clear_fightground(t_fightground *fg) {
    SDL_DestroyTexture(fg->backg_texture);
    SDL_DestroyTexture(fg->floor_texture);
    SDL_DestroyTexture(fg->frontg_texture);
    free(fg);
    fg = NULL;
}