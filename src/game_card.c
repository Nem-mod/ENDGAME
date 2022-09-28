#include "../inc/game_card.h"

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type){
    t_game_card* card = malloc(sizeof(*card));

    switch (type)
    {
    case DMG:
        card->img_path = "resource/img/card_sword.png";
        card->attack = 10;
        card->defence = 0;
        card->cost = 1;
        card->type = DMG;
        break;
    
    case ARM:
        card->img_path = "resource/img/card_shield.png";
        card->attack = 0;
        card->defence = 10;
        card->cost = 1;
        card->type = ARM;
        break;
    case MG:
        card->img_path = "resource/img/card_gold_shield.png";
        card->attack = 5;
        card->defence = 7;
        card->cost = 2;
        card->type = MG;
        break;
    }
    card->rect.h = 150; //мб попробовать другой способ
    card->rect.w = 100;
    card->rect.x = 0;
    card->rect.y = 0;
    card->tex = mx_init_texture(card->img_path, win, rend);
    card->is_active = false;
    return card;
}

void mx_add_buff_card(t_character *player, t_game_card *card) {
    player->attack += card->attack;
    player->shield += card->defence;
    player->current_hp += card->heal;
    if (player->max_hp < player->current_hp)
        player->current_hp = player->max_hp;
}

void mx_sub_buff_card(t_character *player, t_game_card *card) {
    player->attack -= card->attack;
}

void mx_clear_card(t_game_card *card){
    SDL_DestroyTexture(card->tex);
    free(card);
    card = NULL;
}
