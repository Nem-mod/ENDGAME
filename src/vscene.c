#include "../inc/vscene.h"

t_vscene mx_create_vscene(SDL_Window* win, SDL_Renderer* renderer) {
    t_vscene vscene;
    vscene.active = true;
    vscene.rect.h = WINDOW_HEIGHT;
    vscene.rect.w = WINDOW_WIDTH;
    vscene.rect.x = (WINDOW_WIDTH - vscene.rect.w) / 2 ;
    vscene.rect.y = (WINDOW_HEIGHT - vscene.rect.h) / 2;
    vscene.img_path = "resource/img/win_scene.jpg";
    vscene.tex = mx_init_texture(vscene.img_path, win, renderer);
    return vscene;

}
void mx_render_vscene(t_vscene *vscene, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, vscene->tex, NULL,  &vscene->rect);
}

void mx_clear_vscene(t_vscene *vscene) {
    SDL_DestroyTexture(vscene->tex);
}
