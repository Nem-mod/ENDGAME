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
    

    char* enemy_img = "resource/img/fight/enemy.png"; // В отдельной функции создания противника сделать рандом
    fg->enemy_rect.h = 300;
    fg->enemy_rect.w = 300;
    fg->enemy_rect.x = 750;
    fg->enemy_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    fg->enemy = mx_create_character(enemy_img, 20, 1, 1, 1, 1, 1, win, rend);
    mx_set_enemy(fg->enemy);

    fg->player->healthbar = mx_create_bar(win, rend, HEALTH, &fg->player_rect);
    fg->enemy->healthbar = mx_create_bar(win, rend, HEALTH, &fg->enemy_rect);
    fg->player->shieldbar = mx_create_bar(win, rend, SHIELD, &fg->player_rect);
    fg->enemy->shieldbar = mx_create_bar(win, rend, SHIELD, &fg->enemy_rect);

    fg->cards_rect.h = 150;
    fg->cards_rect.w = 450;
    fg->cards_rect.x = (WINDOW_WIDTH - AMOUNT_OF_CARDS * 150) / 2;
    fg->cards_rect.y = (WINDOW_HEIGHT - 150);
    fg->cards_count = 5;

    char* button = "resource/img/button-finish.png";
    fg->button_rect.h = 50;
    fg->button_rect.w = 200;
    fg->button_rect.x = (WINDOW_WIDTH - 200) / 2;
    fg->button_rect.y = (WINDOW_HEIGHT - 75) / 2;

    fg->continue_button = mx_create_button(fg->button_rect.w, fg->button_rect.h, fg->button_rect.x, fg->button_rect.y, button);
    fg->continue_button.tex = mx_init_texture(button, win, rend);
    
    fg->energy = AMOUNT_OF_ENERGY;
    fg->player_action_av = true;
    printf("HP enemy %d\n", fg->enemy->current_hp);
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
    for (int i = 0; i < AMOUNT_OF_CARDS; i++)
    {
        fg->cards[i] = mx_create_card(win, rend, rand() % 2);
        fg->cards[i]->rect.x = fg->cards_rect.x  + i * 155;
        fg->cards[i]->rect.y = fg->cards_rect.y ;
    }
    mx_shift_cards(fg);
}

int mx_render_fightground(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg) {
    mx_update_fight_bars(fg);
    SDL_RenderCopy(rend, fg->backg_texture, NULL, &fg->backg_rect);

    SDL_RenderCopy(rend, fg->floor_texture, NULL, &fg->floor_rect);
    SDL_RenderCopy(rend, fg->frontg_texture, NULL, &fg->frontg_rect);
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        SDL_RenderCopy(rend, fg->cards[i]->tex, NULL, &fg->cards[i]->rect);
    }
    mx_render_character(fg->player, rend, fg->player_rect);
    mx_render_character(fg->enemy, rend, fg->enemy_rect);
    if(mx_fight(win, rend, fg)) {
        return 2;
    }
        
    mx_clear_fightground(&fg);
    return 1;
    
}

void mx_clear_fightground(t_fightground **fg) { // клир кардс нужен
    SDL_DestroyTexture((*fg)->backg_texture);
    SDL_DestroyTexture((*fg)->floor_texture);
    SDL_DestroyTexture((*fg)->frontg_texture);
    free(*fg);
    *fg = NULL;
}

void mx_handle_cards(t_fightground *fg) { // Переделать на перетаскивания
    int active_card = -1;
    int mouse_x;
    int mouse_y;
    int button = SDL_GetMouseState(&mouse_x, &mouse_y);

    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (mx_handle_button(fg->cards[i]->rect)) {
            if (fg->cards[i]->is_active == false) {
                fg->cards[i]->is_active = true;
                fg->energy -= fg->cards[i]->cost;
            }
        }
        else if (!(button & SDL_BUTTON(SDL_BUTTON_LEFT)) && fg->cards[i]->is_active == true) {
            fg->cards[i]->is_active = false;
            fg->energy += fg->cards[i]->cost;
        }
            

        /*if (mx_handle_button(fg->cards[i]->rect)) {
            if (fg->cards[i]->is_active == false && fg->cards[i]->cost <= fg->energy) {
                fg->cards[i]->is_active = true;
                //fg->cards[i]->rect.y -= 10;
                fg->energy -= fg->cards[i]->cost;
            }
            else if (fg->cards[i]->is_active == true){
                fg->cards[i]->is_active = false;
                //fg->cards[i]->rect.y += 10;
                fg->energy += fg->cards[i]->cost;
            }
        }*/
    }
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i]->is_active && active_card != -1)
            printf("ERROR!!!!!!!!!!!!!!!!!!!\n");
        else if(fg->cards[i]->is_active && active_card == -1)
            active_card = i;
    }

    if (active_card != -1) {
        printf("%d is active!\n", active_card);

        fg->cards[active_card]->rect.x = mouse_x - fg->cards[active_card]->rect.w / 2;
        fg->cards[active_card]->rect.y = mouse_y - fg->cards[active_card]->rect.h / 2;
    }
}

bool mx_fight(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg){
    
    if(fg->player_action_av){
        if(fg->player_action_av)
        {
            SDL_RenderCopy(rend, fg->continue_button.tex, NULL, &fg->continue_button.d_rect);
            if(fg->energy >= 0) {
                mx_handle_cards(fg);

            }
            
            if(mx_handle_button(fg->button_rect)) {
                for (int i = 0; i < AMOUNT_OF_CARDS; i++)
                {
                    if(fg->cards[i]->is_active) {
                        mx_add_buff_card(fg->player, fg->cards[i]);
                    }
                }

                mx_calculate_attack(fg->player, fg->enemy);
                if(fg->enemy->current_hp <= 0) {
                    mx_clear_cards(fg->cards);
                    return false;
                }
                fg->energy = AMOUNT_OF_ENERGY;
                fg->player_action_av = false;
            }
        }
    } else {
        printf("FLoppa hp: %d\n", fg->enemy->current_hp);
        mx_calculate_attack(fg->enemy, fg->player);
        mx_create_cards(win, rend, fg);
        fg->player_action_av = true;
    }
    
    return true;
    
}

void mx_update_fight_bars(t_fightground *fg) {
    mx_change_bar(fg->player->healthbar, mx_get_percent_of_int(fg->player->max_hp, fg->player->current_hp));
    mx_change_bar(fg->enemy->healthbar, mx_get_percent_of_int(fg->enemy->max_hp, fg->enemy->current_hp));

    mx_change_bar(fg->player->shieldbar, mx_get_percent_of_int(fg->player->max_hp, fg->player->shield)); // Щит слишком жирный, надо сделать половину от макс хп
    mx_change_bar(fg->enemy->shieldbar, mx_get_percent_of_int(fg->enemy->max_hp, fg->enemy->shield));
}

void mx_clear_cards(t_game_card **cards) {
     for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if(cards[i]->is_active) {
            mx_clear_card(cards[i]);
        }
    }
}
