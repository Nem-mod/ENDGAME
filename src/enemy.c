#include "../inc/enemy.h"

t_enemy mx_create_enemy() {
    t_enemy enemy;
    enemy.active = true;
    enemy.hp = 15;
    enemy.attack = 3;
    enemy.erect.h = 32;
    enemy.erect.w = 32;
    enemy.erect.x = WINDOW_WIDTH / 2;
    enemy.erect.y = WINDOW_WIDTH / 4;
    enemy.img_path = "resource/img/mob.png";
    return enemy;

}
void mx_render_enemy(t_enemy *enemy) {
    enemy->tex = mx_init_texture(enemy->img_path);
    // draw the image to the window
    SDL_Rect erect;
    erect.h = 370;
    erect.w = 380;
    erect.x = 0;
    erect.y = 0;
    SDL_RenderCopy(w_render, enemy->tex, &erect,  &enemy->erect);
}
void mx_clear_enemy(t_enemy *enemy){
    SDL_DestroyTexture(enemy->tex);
}
