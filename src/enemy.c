#include "../inc/enemy.h"

t_enemy mx_create_enemy(SDL_Window* win, SDL_Renderer* renderer) {
    t_enemy enemy;
    enemy.active = true;
    enemy.state = false;
    enemy.hp = 15;
    enemy.attack = 3;
    enemy.erect.h = 64;
    enemy.erect.w = 64;
    enemy.erect.x = WINDOW_WIDTH / 2;
    enemy.erect.y = WINDOW_WIDTH / 4;
    if (!enemy.state)
        enemy.img_path = "resource/img/pmob.png";
    else if (enemy.state)
        enemy.img_path = "resource/img/amob.png";
    enemy.tex = mx_init_texture(enemy.img_path, win, renderer);
    return enemy;

}
void mx_render_enemy(t_enemy *enemy, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, enemy->tex, NULL,  &enemy->erect);
}
void mx_clear_enemy(t_enemy *enemy){
    SDL_DestroyTexture(enemy->tex);
}

