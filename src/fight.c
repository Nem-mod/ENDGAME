#include "../inc/fight.h"

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend, t_character* player) {
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


    fg->player = player;
    fg->cards_rect.h = 150;
    fg->cards_rect.w = 450;
    fg->cards_rect.x = (WINDOW_WIDTH - 450) / 2;
    fg->cards_rect.y = (WINDOW_HEIGHT - 150);
   
    fg->energy = 5;
    
    mx_create_cards(win, rend, fg);
    return fg;
}

void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg) {
    for (int i = 0; i < 3; i++)
    {
        fg->cards[i] = mx_create_card(win, rend, rand() % 3);
        fg->cards[i]->rect.x = fg->cards_rect.x  + i * 150;
        fg->cards[i]->rect.y = fg->cards_rect.y ;
    }
}

void mx_render_fightground(t_fightground *fg, SDL_Renderer *rend) {
    SDL_RenderCopy(rend, fg->backg_texture, NULL, &fg->backg_rect);
    SDL_RenderCopy(rend, fg->floor_texture, NULL, &fg->floor_rect);
    SDL_RenderCopy(rend, fg->frontg_texture, NULL, &fg->frontg_rect);
    for (int i = 0; i < 3; i++) {
        SDL_RenderCopy(rend, fg->cards[i]->tex, NULL, &fg->cards[i]->rect);
    }
}

void mx_clear_fightground(t_fightground *fg) {
    SDL_DestroyTexture(fg->backg_texture);
    SDL_DestroyTexture(fg->floor_texture);
    SDL_DestroyTexture(fg->frontg_texture);
    free(fg);
    fg = NULL;
}
