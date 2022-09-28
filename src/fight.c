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

    fg->player_rect.h = 300;
    fg->player_rect.w = 300;
    fg->player_rect.x = 150;
    fg->player_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    fg->player = player;

    fg->enemy_rect.h = 300;
    fg->enemy_rect.w = 300;
    fg->enemy_rect.x = 750;
    fg->enemy_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    char* enemy_img = "resource/img/fight/enemy.png";
    fg->enemy = mx_create_character(enemy_img, 20, 1, 1, 1, 1, 1, win, rend);
    mx_set_enemy(fg->enemy);

    fg->cards_rect.h = 150;
    fg->cards_rect.w = 450;
    fg->cards_rect.x = (WINDOW_WIDTH - 450) / 2;
    fg->cards_rect.y = (WINDOW_HEIGHT - 150);
    fg->cards_count = 5;


    char* button = "resource/img/button-exit.png";
    fg->button_rect.h = 50;
    fg->button_rect.w = 200;
    fg->button_rect.x = (WINDOW_WIDTH - 200) / 2;
    fg->button_rect.y = (WINDOW_HEIGHT - 75) / 2;

    fg->continue_button = mx_create_button(fg->button_rect.w, fg->button_rect.h, fg->button_rect.x, fg->button_rect.y, button);
    fg->continue_button.tex = mx_init_texture(button, win, rend);
    
    fg->energy = 5;
    fg->player_action_av = true;
    
    mx_create_cards(win, rend, fg);
    return fg;
}

void mx_shift_cards(t_fightground *fg) {
    int margin = (WINDOW_WIDTH - fg->cards_count * 150) / 2;    

    for (int i = 0; i < fg->cards_count; i++) {
        fg->cards[i]->rect.x = margin + i * 150;
    }
}

void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg) {
    for (int i = 0; i < fg->cards_count; i++)
    {
        fg->cards[i] = mx_create_card(win, rend, mx_rand(0,2));
        fg->cards[i]->rect.y = WINDOW_HEIGHT - 150;
    }
    mx_shift_cards(fg);
}

void mx_render_fightground(t_fightground *fg, SDL_Renderer *rend) {
    SDL_RenderCopy(rend, fg->backg_texture, NULL, &fg->backg_rect);

    SDL_RenderCopy(rend, fg->floor_texture, NULL, &fg->floor_rect);
    SDL_RenderCopy(rend, fg->frontg_texture, NULL, &fg->frontg_rect);
    for (int i = 0; i < fg->cards_count; i++) {
        SDL_RenderCopy(rend, fg->cards[i]->tex, NULL, &fg->cards[i]->rect);
    }
    mx_render_character(fg->player, rend, fg->player_rect);
    mx_render_character(fg->enemy, rend, fg->enemy_rect);
    mx_fight(rend, fg);
}

void mx_clear_fightground(t_fightground *fg) {
    SDL_DestroyTexture(fg->backg_texture);
    SDL_DestroyTexture(fg->floor_texture);
    SDL_DestroyTexture(fg->frontg_texture);
    free(fg);
    fg = NULL;
}

void mx_handle_cards(t_fightground *fg) { // Переделать на перетаскивания
    for (int i = 0; i < 3; i++) {
        if (mx_handle_button(fg->cards[i]->rect)) {
            if (fg->cards[i]->is_active == false) {
                fg->cards[i]->is_active = true;
                fg->cards[i]->rect.y -= 10;
            }
            else if (fg->cards[i]->is_active == true){
                fg->cards[i]->is_active = false;
                fg->cards[i]->rect.y += 10;
            }
        }
    }
}

void mx_fight(SDL_Renderer *rend, t_fightground *fg){
    while (fg->enemy->current_hp > 0 || fg->player->current_hp > 0) {
        fg->energy = 5;
        if (fg->player_action_av)
        {
            SDL_RenderCopy(rend, fg->continue_button.tex, NULL, &fg->continue_button.d_rect);
            if(fg->energy <= 0){
                fg->player_action_av = false;
            }
            if(mx_handle_button(fg->button_rect)) {
                fg->player_action_av = false;
            }
            
        }
        break;
    }
    
}
