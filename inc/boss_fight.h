#ifndef BOSSROOM_H
#define BOSSROOM_H
#include "fight.h"

#define AMOUNT_OF_CARDS 5
#define AMOUNT_OF_ENERGY 3
#define P_OF_ENEMYS 3


t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv);
// int mx_render_bossroom(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
// void mx_clear_bossroom(t_fightground **fg);
// bool mx_boss_fight(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);


#endif
