#include "../inc/game_card.h"

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type){
    t_game_card* card = malloc(sizeof(*card));

    switch (type)
    {
    case DMG:
        card = mx_get_card_sword(card);
        break;
    
    case ARM:
        card = mx_get_card_sword(card);
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

t_game_card * mx_get_card_sword(t_game_card *card){
    int value = mx_rand(1, 3);
    switch (value)
    {
    case 1:
        card->img_path = "resource/img/card_sword.png";
        card->attack = 0;
        break;
    
    case 2:
        card->img_path = "resource/img/card_sword2.png";
        card->attack = 4;
        break;
    case 3:
        card->img_path = "resource/img/card_sword3.png";
        card->attack = 7;
        break;
    }
    card->attack += 10 * value;
    card->defence = 0;
    card->cost = value;
    card->type = DMG;
    return card;
}
t_game_card * mx_get_card_shield(t_game_card *card){
    int value = mx_rand(1, 3);
    switch (value)
    {
    case 1:
        card->img_path = "resource/img/card_shield.png";
        break;
    
    case 2:
        card->img_path = "resource/img/card_shield2.png";
        break;
    case 3:
        card->img_path = "resource/img/card_gold_shield.png";
        card->attack = 10;
        break;
    }
    card->defence = 10 * value;
    card->cost = value;
    card->type = ARM;
    return card;
}
void mx_add_buff_card(t_character *player, t_game_card *card) { // В звязи с другой механикой боя, переделать
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
