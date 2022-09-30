#include "../inc/boss_fight.h"

t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv) {
    
    t_fightground *bossground = malloc(sizeof(*bossground));

    bossground->background_path = "resource/img/fight/background.jfif";
    bossground->floor_path = "resource/img/fight/floor.jpg";
    bossground->frontground_path = "resource/img/fight/column.png";

    bossground->backg_rect.x = 0;
    bossground->backg_rect.y = 0;
    bossground->backg_rect.h = WINDOW_HEIGHT / 1.5;
    bossground->backg_rect.w = WINDOW_WIDTH;
    bossground->backg_texture = mx_init_texture(bossground->background_path, win, rend);

    bossground->floor_rect.x = 0;
    bossground->floor_rect.y = WINDOW_HEIGHT / 1.5;
    bossground->floor_rect.h = WINDOW_HEIGHT / 4;
    bossground->floor_rect.w = WINDOW_WIDTH;
    bossground->floor_texture = mx_init_texture(bossground->floor_path, win, rend);

    bossground->frontg_rect.x = 0;
    bossground->frontg_rect.y = 0;
    bossground->frontg_rect.h = WINDOW_HEIGHT / 1.5;
    bossground->frontg_rect.w = WINDOW_WIDTH;
    bossground->frontg_texture = mx_init_texture(bossground->frontground_path, win, rend);

    bossground->player_rect.h = 300;
    bossground->player_rect.w = 300;
    bossground->player_rect.x = 150;
    bossground->player_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    bossground->player = player;
    
    bossground->inv = inv; 
    
    bossground->enemy_rect.h = 300;
    bossground->enemy_rect.w = 300;
    bossground->enemy_rect.x = 750;
    bossground->enemy_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    bossground->enemy = mx_create_character("resource/img/Boss.png", 150, 35, 10, 15, 10, 50, win, rend);


    bossground->player->healthbar = mx_create_bar(win, rend, HEALTH, &bossground->player_rect);
    bossground->enemy->healthbar = mx_create_bar(win, rend, HEALTH, &bossground->enemy_rect);
    bossground->player->shieldbar = mx_create_bar(win, rend, SHIELD, &bossground->player_rect);
    bossground->enemy->shieldbar = mx_create_bar(win, rend, SHIELD, &bossground->enemy_rect);

    bossground->cards_rect.h = 150;
    bossground->cards_rect.w = 450;
    bossground->cards_rect.x = (WINDOW_WIDTH - AMOUNT_OF_CARDS * 150) / 2;
    bossground->cards_rect.y = (WINDOW_HEIGHT - 150);
    bossground->discard_cards_count = 0;

    char* button = "resource/img/button-finish.png";
    bossground->button_rect.h = 50;
    bossground->button_rect.w = 200;
    bossground->button_rect.x = (WINDOW_WIDTH - 200) / 2;
    bossground->button_rect.y = (WINDOW_HEIGHT - 75) / 2;

    bossground->continue_button = mx_create_button(bossground->button_rect.w, bossground->button_rect.h, bossground->button_rect.x, bossground->button_rect.y, button);
    bossground->continue_button.tex = mx_init_texture(button, win, rend);
    
    bossground->energy = AMOUNT_OF_ENERGY;
    bossground->player_action_av = true;
    mx_create_cards(win, rend, bossground, AMOUNT_OF_CARDS);
    bossground->exit_flag = false;
    return bossground;
}

int mx_render_bossroom(SDL_Window *win, SDL_Renderer *rend, t_fightground* bossroom) {
    mx_update_fight_bars(bossroom);
    SDL_RenderCopy(rend, bossroom->backg_texture, NULL, &bossroom->backg_rect);

    SDL_RenderCopy(rend, bossroom->floor_texture, NULL, &bossroom->floor_rect);
    SDL_RenderCopy(rend, bossroom->frontg_texture, NULL, &bossroom->frontg_rect);
    mx_render_character(bossroom->player, rend, bossroom->player_rect);
    SDL_RenderCopy(rend, bossroom->enemy->character_texture, NULL, &bossroom->enemy_rect);
    mx_render_bar(bossroom->enemy->healthbar, rend);
    mx_render_bar(bossroom->enemy->shieldbar, rend);
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (bossroom->cards[i] != NULL && bossroom->cards[i]->is_active == false)
            SDL_RenderCopy(rend, bossroom->cards[i]->tex, NULL, &bossroom->cards[i]->rect);
    }
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (bossroom->cards[i] != NULL && bossroom->cards[i]->is_active == true)
            SDL_RenderCopy(rend, bossroom->cards[i]->tex, NULL, &bossroom->cards[i]->rect);
    }

    if (bossroom->player->current_hp <= 0) {
        return DEATH;
    }
    if(!bossroom->exit_flag) {
        
        mx_fight(win, rend, bossroom); // ИЗМЕНИТЬ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(bossroom->enemy->current_hp <= 0){
            SDL_DestroyTexture( bossroom->enemy->character_texture);
            bossroom->enemy->character_texture = mx_init_texture("resource/img/dm.png", win, rend);
            if(mx_handle_button(bossroom->button_rect)) {
                bossroom->exit_flag = true;
            }
        }
        return BOSSFIGHT;
    }
    
    
    
    bossroom->player->shield = 0;
    mx_clear_fightground(&bossroom);
    return MAP;
}

