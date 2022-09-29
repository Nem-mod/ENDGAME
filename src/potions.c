#include "../inc/potions.h"

t_potion* mx_create_potion(SDL_Window* win, SDL_Renderer* renderer){
    t_potion* potion = malloc(sizeof(*potion));

    potion->img_path = "resource/img/health_potion.png";
    potion->rect.h = 50; //мб попробовать другой способ
    potion->rect.w = 50;
    potion->rect.x = 0;
    potion->rect.y = 0;
    potion->tex = mx_init_texture(potion->img_path, win, renderer);
    return potion;
}
void mx_clear_potion(t_potion* potion);

t_potion_bar* mx_create_potion_bar(SDL_Window* win, SDL_Renderer* renderer) {
    t_potion_bar* potion_bar = malloc(sizeof(*potion_bar));
    potion_bar->img_path = "resource/img/bar_border.png";
    potion_bar->rect.h = 50;
    potion_bar->rect.w = 150;
    potion_bar->rect.x = 50;
    potion_bar->rect.y = 50;
    potion_bar->tex = mx_init_texture(potion_bar->img_path, win, renderer);
    printf("%s", potion_bar->img_path);
    for (int i = 0; i < MAX_AMOUNT_OF_PT; i++){
        potion_bar->potions[i] = mx_create_potion(win, renderer);
        potion_bar->potions[i]->rect.x = potion_bar->rect.x  + i * 50;
        potion_bar->potions[i]->rect.y = potion_bar->rect.y;
    }
    
    return potion_bar;
}
void mx_render_potion_bar(t_potion_bar* potions, SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, potions->tex, NULL, &potions->rect);
    for(int i = 0; i < MAX_AMOUNT_OF_PT; i++) {
        SDL_RenderCopy(renderer, potions->potions[i]->tex, NULL, &potions->potions[i]->rect);
    }
}
void mx_clear_potion_bar(t_potion_bar* potions);
