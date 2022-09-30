#include "../inc/boss_fight.h"

t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv) {
    
    t_fightground *bossroom = malloc(sizeof(*bossroom));

    bossroom->background_path = "resource/img/fight/background.jfif";
    bossroom->floor_path = "resource/img/fight/floor.jpg";
    bossroom->frontground_path = "resource/img/fight/column.png";

    bossroom->backg_rect.x = 0;
    bossroom->backg_rect.y = 0;
    bossroom->backg_rect.h = WINDOW_HEIGHT / 1.5;
    bossroom->backg_rect.w = WINDOW_WIDTH;
    bossroom->backg_texture = mx_init_texture(bossroom->background_path, win, rend);

    bossroom->floor_rect.x = 0;
    bossroom->floor_rect.y = WINDOW_HEIGHT / 1.5;
    bossroom->floor_rect.h = WINDOW_HEIGHT / 4;
    bossroom->floor_rect.w = WINDOW_WIDTH;
    bossroom->floor_texture = mx_init_texture(bossroom->floor_path, win, rend);

    bossroom->frontg_rect.x = 0;
    bossroom->frontg_rect.y = 0;
    bossroom->frontg_rect.h = WINDOW_HEIGHT / 1.5;
    bossroom->frontg_rect.w = WINDOW_WIDTH;
    bossroom->frontg_texture = mx_init_texture(bossroom->frontground_path, win, rend);

    bossroom->player_rect.h = 300;
    bossroom->player_rect.w = 300;
    bossroom->player_rect.x = 150;
    bossroom->player_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    bossroom->player = player;
    
    bossroom->inv = inv; 
    
    bossroom->enemy_rect.h = 300;
    bossroom->enemy_rect.w = 300;
    bossroom->enemy_rect.x = 750;
    bossroom->enemy_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    bossroom->enemy = mx_create_character("resource/img/Boss.png", 150, 27, 10, 15, 10, 50, win, rend);


    bossroom->player->healthbar = mx_create_bar(win, rend, HEALTH, &bossroom->player_rect);
    bossroom->enemy->healthbar = mx_create_bar(win, rend, HEALTH, &bossroom->enemy_rect);
    bossroom->player->shieldbar = mx_create_bar(win, rend, SHIELD, &bossroom->player_rect);
    bossroom->enemy->shieldbar = mx_create_bar(win, rend, SHIELD, &bossroom->enemy_rect);

    bossroom->cards_rect.h = 150;
    bossroom->cards_rect.w = 450;
    bossroom->cards_rect.x = (WINDOW_WIDTH - AMOUNT_OF_CARDS * 150) / 2;
    bossroom->cards_rect.y = (WINDOW_HEIGHT - 150);
    bossroom->discard_cards_count = 0;

    char* button = "resource/img/button-finish.png";
    bossroom->button_rect.h = 50;
    bossroom->button_rect.w = 200;
    bossroom->button_rect.x = (WINDOW_WIDTH - 200) / 2;
    bossroom->button_rect.y = (WINDOW_HEIGHT - 75) / 2;

    bossroom->continue_button = mx_create_button(bossroom->button_rect.w, bossroom->button_rect.h, bossroom->button_rect.x, bossroom->button_rect.y, button);
    bossroom->continue_button.tex = mx_init_texture(button, win, rend);
    
    bossroom->energy = AMOUNT_OF_ENERGY;
    bossroom->player_action_av = true;
    mx_create_cards(win, rend, bossroom, AMOUNT_OF_CARDS);
    bossroom->exit_flag = false;
    return bossroom;
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
    SDL_RenderCopy(rend, bossroom->continue_button.tex, NULL, &bossroom->button_rect);
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
    return VICTORY;
}

