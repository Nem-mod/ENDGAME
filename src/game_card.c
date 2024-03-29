#include "../inc/game_card.h"

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type, int lvl){
    t_game_card* card = malloc(sizeof(*card));

    card->attack = 0;
    card->defence = 0;
    card->heal = 0;
    switch (type)
    {
    case DMG:
        card = mx_get_card_sword(card, lvl);
        break;
    
    case ARM:
        card = mx_get_card_shield(card, lvl);
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

t_game_card * mx_get_card_sword(t_game_card *card, int lvl){
    int value = 1;
    int v = 0;
    if (lvl == 0) {
        if(mx_rand(1, 100) > 80) {
        value = 3;
        }
        if(mx_rand(1, 100) > 50) {
            value = 2;
        }
    }
    else
        value = lvl;

    switch (value)
    {
    case 1:
        
        card->img_path = "resource/img/card_sword.png";
        card->attack = 0;
        break;
    
    case 2:
        v = mx_rand(0, 100);
        if(v > 50)
            card->img_path = "resource/img/card_sword2.png";
        else
        card->img_path = "resource/img/sword22.png";
        card->attack = 6;
        break;
    case 3:
        v = mx_rand(0, 100);
        if(v > 50)
            card->img_path = "resource/img/card_sword3.png";
        else
        card->img_path = "resource/img/satt.png";
        card->attack = 10;
        break;
    }
    card->attack += 10 * value;
    card->cost = value;
    card->type = DMG;
    return card;
}
t_game_card * mx_get_card_shield(t_game_card *card, int lvl){
    int value = 1;
    int v = 0;
    if (lvl == 0) {
        if(mx_rand(1, 100) > 90) {
            value = 3;
        }
        if(mx_rand(1, 100) > 60) {
            value = 2;
        }
    }
    else
        value = lvl;

    switch (value)
    {
    case 1:
        card->img_path = "resource/img/card_shield.png";
        card->defence = 0;
        break;
    
    case 2:
        card->img_path = "resource/img/card_shield2.png";
        card->defence = 4;
        break;
    case 3:
        v = mx_rand(0, 100);
        if(v > 50)
            card->img_path = "resource/img/card_gold_shield.png";
        else
        card->img_path = "resource/img/shield32.png";
        card->defence = 7;
        break;
    }
    card->defence += 10 * value;
    card->cost = value;
    card->type = ARM;
    return card;
}

void mx_activate_card(t_character *player, t_game_card *card) {
    mx_calculate_card_attack(card, player);
    player->shield += card->defence;
    player->current_hp += card->heal;
    if (player->max_hp < player->current_hp)
        player->current_hp = player->max_hp;
    if (player->max_hp < player->shield)
        player->shield = player->max_hp;
}

int mx_calculate_card_attack(t_game_card *from, t_character *to) {
    int cur_dmg = from->attack;

    if (mx_chance(to->dodge_chance))
        return -1; // -1 означает dodge. Надо придумать чет с этим и мб переделать т.к -1 не понять нихуя

    cur_dmg = mx_int_dispersion(cur_dmg, DMG_DISP_PERCENT);

    cur_dmg -= to->shield;
    to->shield = -cur_dmg;

    if (cur_dmg < 0)
        cur_dmg = 0;
    if (to->shield < 0)
        to->shield = 0;

    to->current_hp -= cur_dmg; // Надо ли отнимать в функции, или лучше каждый раз вручную?
    return cur_dmg;
}

t_game_card *mx_copy_card(t_game_card *src, SDL_Window *win, SDL_Renderer *rend) {
    t_game_card *card = malloc(sizeof(*card));

    card->attack = src->attack;
    card->defence = src->defence;
    card->heal = src->heal;
    card->cost = src->cost;
    card->type = src->type;
    card->img_path = src->img_path;
    card->rect.x = src->rect.x;
    card->rect.y = src->rect.y;
    card->rect.h = src->rect.h;
    card->rect.w = src->rect.w;
    card->tex = mx_init_texture(card->img_path, win, rend);
    card->is_active = src->is_active;

    return card;
}

void mx_clear_card(t_game_card *card){
    SDL_DestroyTexture(card->tex);
    free(card);
    card = NULL;
}
