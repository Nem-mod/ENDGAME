#ifndef BOSSROOM_H
#define BOSSROOM_H
#include "fight.h"

#define AMOUNT_OF_CARDS 5
#define AMOUNT_OF_ENERGY 3


t_fightground *mx_create_bossroom(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv);
int mx_render_bossroom(SDL_Window *win, SDL_Renderer *rend, t_fightground* bossroom);


#endif
