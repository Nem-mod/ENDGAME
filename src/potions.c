#include "../inc/potions.h"

t_potion* mx_create_potion(SDL_Window* win, SDL_Renderer* renderer){
    t_potion* potion = malloc(sizeof(*potion));
    potion->value = 30;
    potion->img_path = "resource/img/health_potion.png";
    potion->rect.h = 50;
    potion->rect.w = 50;
    potion->rect.x = 0;
    potion->rect.y = 0;
    potion->tex = mx_init_texture(potion->img_path, win, renderer);
    return potion;
}
void mx_clear_potion(t_potion* potion);

t_potion_bar* mx_create_potion_bar(SDL_Window* win, SDL_Renderer* renderer) {
    t_potion_bar* potions_bar = malloc(sizeof(*potions_bar));
    potions_bar->img_path = "resource/img/bar_border.png";
    potions_bar->rect.h = 50;
    potions_bar->rect.w = 150;
    potions_bar->rect.x = 50;
    potions_bar->rect.y = 50;
    potions_bar->tex = mx_init_texture(potions_bar->img_path, win, renderer);
    potions_bar->potions_count = MAX_AMOUNT_OF_PT;
    for (int i = 0; i < potions_bar->potions_count; i++){
        potions_bar->potions[i] = mx_create_potion(win, renderer);
        potions_bar->potions[i]->rect.x = potions_bar->rect.x  + i * 50;
        potions_bar->potions[i]->rect.y = potions_bar->rect.y;
    }
    
    return potions_bar;
}
void mx_render_potion_bar(t_potion_bar* potions_bar, SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, potions_bar->tex, NULL, &potions_bar->rect);
    for(int i = 0; i < potions_bar->potions_count; i++) {
        SDL_RenderCopy(renderer, potions_bar->potions[i]->tex, NULL, &potions_bar->potions[i]->rect);
    }
}
void mx_clear_potion_bar(t_potion_bar* potions_bar) {
    SDL_DestroyTexture(potions_bar->tex);
    free(potions_bar);
    potions_bar = NULL;
}

void mx_handle_potion(t_potion_bar *potions_bar, t_character *player){
    for (int i = 0; i < potions_bar->potions_count; i++) {
        if(mx_handle_button(potions_bar->potions[i]->rect)) {
            if(player->current_hp + potions_bar->potions[i]->value > player->max_hp) {
                player->current_hp = player->max_hp;
            } else {
                player->current_hp += potions_bar->potions[i]->value;
            }
            potions_bar->potions_count--;
            SDL_Delay(100);
        }

    }
    
}
