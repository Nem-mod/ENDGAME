#ifndef FIGHTGROUND_H
#define FIGHTGROUND_H
#include "window_sdl.h"
#include "character.h"
#include "game_card.h"

typedef struct  s_fightground {
    char *background_path;
    char *floor_path;
    char *frontground_path;
    char **cards_path; // Будет отдельная структура для карточек

    int energy;

    SDL_Rect backg_rect;
    SDL_Rect floor_rect;
    SDL_Rect frontg_rect;
    SDL_Rect cards_rect;
    SDL_Rect player_rect;
    SDL_Rect enemy_rect;


    SDL_Texture *backg_texture;
    SDL_Texture *floor_texture;
    SDL_Texture *frontg_texture;
    
    t_character* player;
    t_character* enemy;
    t_game_card* cards[3];

}               t_fightground;

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend, t_character* player);
void mx_render_fightground(t_fightground *fg, SDL_Renderer *rend);
void mx_clear_fightground(t_fightground *fg);
void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);

#endif
