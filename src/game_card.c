#include "../inc/game_card.h"

t_game_card* mx_create_card(SDL_Window *win, SDL_Renderer *rend, t_card_type type){
    t_game_card* card = malloc(sizeof(*card));

    card->cost = rand() % 2 + 1;
    card->value = rand() % 4 + 3;
    switch (type)
    {
    case DMG:
        card->img_path = "resource/img/card_sword.png";
        break;
    
    case ARM:
        card->img_path = "resource/img/card_shield.png";
        break;
    case MG:
        card->img_path = "resource/img/card_gold_shield.png";
        break;
    }
    card->rect.h = 150;
    card->rect.w = 100;
    card->rect.x = 0;
    card->rect.y = 0;
    card->tex = mx_init_texture(card->img_path, win, rend);
    return card;
}

void mx_clear_card(t_game_card *card){
    SDL_DestroyTexture(card->tex);
    free(card);
    card = NULL;
}
