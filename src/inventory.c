#include "../inc/inventory.h"

void mx_create_inventory(SDL_Window *win, SDL_Renderer *rend) {
    t_inventory *inv = malloc(sizeof(*inv));

    inv->inv_path = "resource/img/inventory.png";

    inv->rect.x = 0;
    inv->rect.y = 0;
    inv->texture = mx_init_texture(inv->inv_path, win, rend);
    SDL_QueryTexture(inv->texture, NULL, NULL, &inv->rect.w, &inv->rect.h); 
}

void mx_render_inventory(SDL_Renderer *rend, t_inventory *inv) {
    for (int i = 0; i < inv->current_cards; i++) {
        if (inv->cards[i] != NULL && inv->cards[i]->is_active == false)
            SDL_RenderCopy(rend, inv->cards[i]->tex, NULL, &inv->cards[i]->rect);
    }
    for (int i = 0; i < inv->current_cards; i++) {
        if (inv->cards[i] != NULL && inv->cards[i]->is_active == true)
            SDL_RenderCopy(rend, inv->cards[i]->tex, NULL, &inv->cards[i]->rect);
    }
}

void mx_generate_start_cards(SDL_Window *win, SDL_Renderer *rend, t_inventory *inv) {
    inv->current_cards = START_AMOUNT_OF_CARDS;
    for (int i = 0; i < START_AMOUNT_OF_CARDS; i++)
        inv->cards[i] = mx_create_card(win, rend, mx_rand(0, CARD_TYPE_COUNT - 1), 1);
}

void mx_add_card_to_inventory(t_inventory *inv, t_game_card *src_card, SDL_Window *win, SDL_Renderer *rend) {
    t_game_card *card = mx_copy_card(src_card, win, rend);
    
    inv->cards[inv->current_cards] = card;
    inv->current_cards++;
}
