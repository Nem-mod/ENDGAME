#include "../inc/boss_fight.h"

t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player) {
    t_fightground *boss_room = mx_create_fightground(win, rend, player);

    boss_room->enemy->character_path = "../resource/img/Boss.png";
    boss_room->enemy->max_hp *= 1.5;
    boss_room->enemy->attack *= 2;


    return boss_room;
}
