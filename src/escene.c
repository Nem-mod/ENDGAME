#include "../inc/escene.h"

t_escene mx_create_escene(SDL_Window* win, SDL_Renderer* renderer) {
    t_escene escene;
    escene.active = true;
    escene.rect.h = WINDOW_HEIGHT;
    escene.rect.w = WINDOW_WIDTH;
    escene.rect.x = (WINDOW_WIDTH - escene.rect.w) / 2 ;
    escene.rect.y = (WINDOW_HEIGHT - escene.rect.h) / 2;
    escene.img_path = "resource/img/died.jpg";
    escene.tex = mx_init_texture(escene.img_path, win, renderer);
    return escene;

}
void mx_render_escene(t_escene *escene, SDL_Renderer *renderer) {
    // draw the image to the window
    SDL_RenderCopy(renderer, escene->tex, NULL,  &escene->rect);
}

void mx_clear_escene(t_escene *escene){
    SDL_DestroyTexture(escene->tex);
}
