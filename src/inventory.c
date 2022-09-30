#include "../inc/inventory.h"

t_inventory *mx_create_inventory(SDL_Window *win, SDL_Renderer *rend) {
    t_inventory *inv = malloc(sizeof(*inv));

    inv->inv_path = "resource/img/invent.png";

    inv->rect.x = 0;
    inv->rect.y = 0;
    inv->texture = mx_init_texture(inv->inv_path, win, rend);
    SDL_QueryTexture(inv->texture, NULL, NULL, &inv->rect.w, &inv->rect.h); 

    return inv;
}

void mx_render_inventory(SDL_Renderer *rend, t_inventory *inv) {
    SDL_RenderCopy(rend, inv->texture, NULL, &inv->rect);
    mx_shift_inventory_cards(inv);
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

bool mx_add_card_to_inventory(t_inventory *inv, t_game_card *src_card, SDL_Window *win, SDL_Renderer *rend) {
    
    if (inv->current_cards < MAX_CARDS) {
        t_game_card *card = mx_copy_card(src_card, win, rend);
    
        inv->cards[inv->current_cards] = card;
        inv->current_cards++;
        return true;
    }
    return false;
}

void mx_shift_inventory_cards(t_inventory *inv) {
    int margin = (WINDOW_WIDTH - inv->current_cards * 150) / 2;    
    int shif_count = 0;

    for (int i = 0; i < inv->current_cards; i++) {
        if (inv->cards[i] != NULL) {
            inv->cards[i]->rect.x = (margin + 150 - 150 / 5 - inv->cards[i]->rect.w) + shif_count * 150;
            inv->cards[i]->rect.y = inv->rect.y + (inv->rect.h / 2 - inv->cards[i]->rect.h / 2);
            shif_count++;
        }
    }
}

void mx_clear_inventory(t_inventory *inv) {
    for (int i = 0; i < inv->current_cards; i++) {
        mx_clear_card(inv->cards[i]);
        inv->cards[i] = NULL;
    }
    SDL_DestroyTexture(inv->texture);
    free(inv);
    inv = NULL;
}
