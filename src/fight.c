#include "../inc/fight.h"

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv, int diff) {
    
    t_fightground *fg = malloc(sizeof(*fg));

    if(mx_rand(0, 1) == 1) {
        fg->background_path = "resource/img/fight/back_1.png";
        fg->floor_path = "resource/img/fight/ground_1.png";
    } else {
        fg->background_path = "resource/img/fight/back_2.png";
        fg->floor_path = "resource/img/fight/ground_2.png";
    }
    
    fg->button_path = "resource/img/button-finish.png";
    fg->dm_path = "resource/img/dm.png";
    fg->bag_path = "resource/img/bag.png";

    fg->energy_ind_path[0] = "resource/img/indicator1.png",
    fg->energy_ind_path[1] = "resource/img/indicator2.png";
    fg->energy_ind_path[2] = "resource/img/indicator3.png";
    fg->energy_ind_path[3] = "resource/img/indicator4.png";

    fg->backg_rect.x = 0;
    fg->backg_rect.y = 0;
    fg->backg_rect.h = WINDOW_HEIGHT / 1.2;
    fg->backg_rect.w = WINDOW_WIDTH;
    fg->backg_texture = mx_init_texture(fg->background_path, win, rend);

    fg->floor_rect.x = 0;
    fg->floor_rect.y = WINDOW_HEIGHT / 1.5;
    fg->floor_rect.h = WINDOW_HEIGHT / 3.5;
    fg->floor_rect.w = WINDOW_WIDTH;
    fg->floor_texture = mx_init_texture(fg->floor_path, win, rend);

    for (int i = 0; i < 4; i++)
        fg->energy_ind_texture[i] = mx_init_texture(fg->energy_ind_path[i], win, rend);

    fg->player_rect.h = 300;
    fg->player_rect.w = 300;
    fg->player_rect.x = 150;
    fg->player_rect.y = WINDOW_HEIGHT / 1.5 - 150;
    fg->player = player;

    fg->inv = inv;    

    char* enemys_img[P_OF_ENEMYS] = {
        "resource/img/chest_def3.png",
        "resource/img/firebock.png",
        "resource/img/goblin.png",
        "resource/img/bear.png",
        "resource/img/player_reverse.png",
        }; // В отдельной функции создания противника сделать рандом

    fg->enemy_rect.h = 300;
    fg->enemy_rect.w = 300;
    fg->enemy_rect.x = 750;
    fg->enemy_rect.y = WINDOW_HEIGHT / 1.5 - 150;
    int pos = mx_rand(0, P_OF_ENEMYS - 1);
    fg->enemy = mx_create_character(enemys_img[pos], 20, 1, 1, 1, 1, 1, win, rend);

    mx_set_enemy(fg->enemy);
    if (diff <= 2) {
        fg->enemy->max_hp -= 40;
        fg->enemy->current_hp = fg->enemy->max_hp;
        fg->enemy->attack -= 15;
    }
    else if (diff <= 4) {
        fg->enemy->max_hp -= 20;
        fg->enemy->current_hp = fg->enemy->max_hp;
        fg->enemy->attack -= 10;
    }

    fg->player->healthbar = mx_create_bar(win, rend, HEALTH, &fg->player_rect);
    fg->enemy->healthbar = mx_create_bar(win, rend, HEALTH, &fg->enemy_rect);
    fg->player->shieldbar = mx_create_bar(win, rend, SHIELD, &fg->player_rect);
    fg->enemy->shieldbar = mx_create_bar(win, rend, SHIELD, &fg->enemy_rect);

    fg->cards_rect.h = 150;
    fg->cards_rect.w = 450;
    fg->cards_rect.x = (WINDOW_WIDTH - AMOUNT_OF_CARDS * 150) / 2;
    fg->cards_rect.y = (WINDOW_HEIGHT - 150);
    fg->discard_cards_count = 0;

    fg->button_rect.h = 50;
    fg->button_rect.w = 200;
    fg->button_rect.x = (WINDOW_WIDTH - 200) / 2;
    fg->button_rect.y = (WINDOW_HEIGHT - 75) / 3;

    fg->continue_button = mx_create_button(fg->button_rect.w, fg->button_rect.h, fg->button_rect.x, fg->button_rect.y, fg->button_path);
    fg->continue_button.tex = mx_init_texture(fg->button_path, win, rend);

    SDL_QueryTexture(fg->energy_ind_texture[0], NULL, NULL, &fg->energy_ind_rect.w, &fg->energy_ind_rect.h);
    fg->energy_ind_rect.w *= 2;
    fg->energy_ind_rect.h *= 2;
    fg->energy_ind_rect.x = WINDOW_WIDTH - fg->energy_ind_rect.w - 50;
    fg->energy_ind_rect.y = 50;
    
    fg->energy = AMOUNT_OF_ENERGY;
    fg->player_action_av = true;
    fg->win_flag = false;
    mx_create_cards(win, rend, fg, AMOUNT_OF_CARDS);
    fg->exit_flag = false;
    return fg;
}

void mx_shift_cards(t_fightground *fg) {
    int margin = (WINDOW_WIDTH - (AMOUNT_OF_CARDS - fg->discard_cards_count) * 150) / 2;    
    int shif_count = 0;

    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i] != NULL) {
            fg->cards[i]->rect.x = (margin) + shif_count * 150;
            fg->cards[i]->rect.y = fg->cards_rect.y;
            shif_count++;
        }
    }
}

void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg, int cards_ammount) {
    for (int i = 0; i < cards_ammount; i++) {
        fg->cards[i] = mx_copy_card(fg->inv->cards[mx_rand(0, fg->inv->current_cards - 1)], win, rend);
        fg->cards[i]->is_active = false;
    }
    mx_shift_cards(fg);
}

int mx_render_fightground(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg) {
    mx_update_fight_bars(fg);
    SDL_RenderCopy(rend, fg->backg_texture, NULL, &fg->backg_rect);

    SDL_RenderCopy(rend, fg->floor_texture, NULL, &fg->floor_rect);
    mx_render_character(fg->player, rend, fg->player_rect);
    mx_render_character(fg->enemy, rend, fg->enemy_rect);
    SDL_RenderCopy(rend, fg->continue_button.tex, NULL, &fg->continue_button.d_rect);
    if (!fg->win_flag)
        SDL_RenderCopy(rend, fg->energy_ind_texture[fg->energy], NULL, &fg->energy_ind_rect);

    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i] != NULL && fg->cards[i]->is_active == false) {
            SDL_RenderCopy(rend, fg->cards[i]->tex, NULL, &fg->cards[i]->rect);
        }
    }
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i] != NULL && fg->cards[i]->is_active == true) {
            SDL_RenderCopy(rend, fg->cards[i]->tex, NULL, &fg->cards[i]->rect);
        }
    }

    if (fg->player->current_hp <= 0) {
        return DEATH;
    }
    if(!fg->exit_flag) {
        if (fg->enemy->current_hp <= 0 && !fg->win_flag) {
            fg->discard_cards_count = 0;
            mx_win_level(win, rend, fg);
        }
        mx_fight(win, rend, fg);

        return LEVEL;
    }
    
    
    fg->player->shield = 0;
    mx_clear_fightground(&fg);
    return MAP;
    
}

void mx_win_level(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg) {
    
    SDL_DestroyTexture(fg->enemy->character_texture);
    fg->enemy->character_texture = mx_init_texture(fg->dm_path, win, rend);
    fg->enemy_rect.w = 100;
    fg->enemy_rect.h = 100;
    fg->enemy_rect.x = 900;
    fg->enemy_rect.y = WINDOW_HEIGHT / 1.5;
    SDL_DestroyTexture(fg->continue_button.tex);
    fg->continue_button.tex = mx_init_texture(fg->bag_path, win, rend);
    fg->continue_button.d_rect.w = 100;
    fg->continue_button.d_rect.h = 100;
    fg->continue_button.d_rect.x = fg->player_rect.x + fg->player_rect.w + fg->continue_button.d_rect.w;
    fg->continue_button.d_rect.y = fg->player_rect.y + fg->player_rect.h - fg->continue_button.d_rect.h * 2;
    fg->win_flag = true;
    fg->energy = AMOUNT_OF_ENERGY;

    mx_clear_cards(fg);
    for (int i = 0; i < 3; i++) {
        fg->cards[i] = mx_create_card(win, rend, mx_rand(0, 1), 0);
    }
    // for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
    //     if (fg->cards[i] != NULL)
    //         printf("%d not null\n", i);
    //     else
    //         printf("%d null\n", i);
    // }
    fg->discard_cards_count = AMOUNT_OF_CARDS - 3;
    mx_shift_cards(fg);
    
}

void mx_clear_fightground(t_fightground **fg) {
    SDL_DestroyTexture((*fg)->backg_texture);
    SDL_DestroyTexture((*fg)->floor_texture);
    //SDL_DestroyTexture((*fg)->frontg_texture);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture((*fg)->energy_ind_texture[i]);
    mx_clear_cards(*fg);
    free(*fg);
    *fg = NULL;
}

void mx_handle_cards(t_fightground *fg, SDL_Window *win, SDL_Renderer *rend) {
    int active_card = -1;
    int mouse_x;
    int mouse_y;
    int button = SDL_GetMouseState(&mouse_x, &mouse_y);

    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i] != NULL) {
           if (fg->cards[i]->is_active && active_card != -1)
                printf("ERROR!\n");
            else if(fg->cards[i]->is_active && active_card == -1)
                active_card = i; 
        }
        
    }
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (fg->cards[i] != NULL) {
            if (mx_handle_button(fg->cards[i]->rect) && fg->energy >= fg->cards[i]->cost) {
                if (fg->cards[i]->is_active == false && active_card == -1) {
                    fg->cards[i]->is_active = true;
                    fg->energy -= fg->cards[i]->cost;
                }
            }
            else if (!(button & SDL_BUTTON(SDL_BUTTON_LEFT)) && fg->cards[i]->is_active == true) {
                if ((mx_cursor_on_button(fg->enemy_rect) || mx_cursor_on_button(fg->player_rect)) && !fg->win_flag) {
                    if (mx_cursor_on_button(fg->enemy_rect))
                        mx_activate_card(fg->enemy, fg->cards[i]);
                    else
                        mx_activate_card(fg->player, fg->cards[i]);
                    mx_clear_card(fg->cards[i]);
                    fg->cards[i] = NULL;
                    fg->discard_cards_count++;
                    mx_shift_cards(fg);
                    active_card = -1;
                }
                else if (mx_cursor_on_button(fg->continue_button.d_rect)) {
                    mx_add_card_to_inventory(fg->inv, fg->cards[i], win, rend);
                    fg->exit_flag = true;
                }
                else {
                    fg->cards[i]->is_active = false;
                    fg->energy += fg->cards[i]->cost;
                    active_card = -1;
                    mx_shift_cards(fg);
                }
            }
        }
    }

    if (active_card != -1) {
        fg->cards[active_card]->rect.x = mouse_x - fg->cards[active_card]->rect.w / 2;
        fg->cards[active_card]->rect.y = mouse_y - fg->cards[active_card]->rect.h / 2;
    }
}

void mx_fight(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg){
    if(fg->player_action_av){
        if(fg->energy >= 0) {
            mx_handle_cards(fg, win, rend);
        }
        
        if(mx_handle_button(fg->button_rect) && !fg->win_flag) {
            if(fg->enemy->current_hp <= 0) {
                mx_clear_cards(fg);
            }
            fg->discard_cards_count = 0;
            fg->energy = AMOUNT_OF_ENERGY;
            fg->player_action_av = false;
            //mx_calculate_character_attack(fg->player, fg->enemy);
            SDL_Delay(100); // Поменять на подсчет времени. Мб тупаяя и сложная идея
        }
    } else {
        if (fg->enemy->current_hp > 0) {
            mx_calculate_character_attack(fg->enemy, fg->player);
            mx_create_cards(win, rend, fg, AMOUNT_OF_CARDS);
            fg->player_action_av = true;
        }
    }
}

void mx_update_fight_bars(t_fightground *fg) {
    mx_change_bar(fg->player->healthbar, mx_get_percent_of_int(fg->player->max_hp, fg->player->current_hp));
    mx_change_bar(fg->enemy->healthbar, mx_get_percent_of_int(fg->enemy->max_hp, fg->enemy->current_hp));

    mx_change_bar(fg->player->shieldbar, mx_get_percent_of_int(fg->player->max_hp, fg->player->shield)); // Щит слишком жирный, надо сделать половину от макс хп
    mx_change_bar(fg->enemy->shieldbar, mx_get_percent_of_int(fg->enemy->max_hp, fg->enemy->shield));
}

void mx_clear_cards(t_fightground *fg) {
    for (int i = 0; i <= AMOUNT_OF_CARDS; i++) {
        if(fg->cards[i] != NULL) {
            mx_clear_card(fg->cards[i]);
        }
        fg->cards[i] = NULL;
    }
}
