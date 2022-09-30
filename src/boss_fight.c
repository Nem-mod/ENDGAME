#include "../inc/boss_fight.h"

t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv) {
    t_fightground *boss_room = mx_create_fightground(win, rend, player, inv);


    mx_clear_character(boss_room->enemy);
    boss_room->enemy = mx_create_character("resource/img/Boss.png",
     150, 25, 15, 40, 10, 0, win, rend);
    printf("After creating BOSS\n");

    return boss_room;
}

int mx_render_bossroom(SDL_Window *win, SDL_Renderer *rend, t_fightground* bossroom, t_inventory *inv) {
    mx_update_fight_bars(bossroom);
    printf("After updating fightbars\n");
    SDL_RenderCopy(rend, bossroom->backg_texture, NULL, &bossroom->backg_rect);

    SDL_RenderCopy(rend, bossroom->floor_texture, NULL, &bossroom->floor_rect);
    SDL_RenderCopy(rend, bossroom->frontg_texture, NULL, &bossroom->frontg_rect);
    mx_render_character(bossroom->player, rend, bossroom->player_rect);
    printf("Before render copy\n");
    SDL_RenderCopy(rend, bossroom->enemy->character_texture, NULL, &bossroom->enemy_rect);
    printf("Before render hp bar\n");
    mx_render_bar(bossroom->enemy->healthbar, rend);
    printf("Before render shield bar\n");
    // mx_render_bar(bossroom->enemy->shieldbar, rend);
    printf("After rendering boss\n");
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
        
        mx_fight(win, rend, bossroom, inv);
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

