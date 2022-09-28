#ifndef FIGHTGROUND_H
#define FIGHTGROUND_H
#include "window_sdl.h"
#include "character.h"
#include "game_card.h"
#include "button.h"

#define AMOUNT_OF_CARDS 5
#define AMOUNT_OF_ENERGY 3
typedef struct  s_fightground {
    char *background_path;
    char *floor_path;
    char *frontground_path;

    int energy;

    SDL_Rect backg_rect;
    SDL_Rect floor_rect;
    SDL_Rect frontg_rect;

    SDL_Rect player_rect;
    SDL_Rect enemy_rect;
    SDL_Rect cards_rect;
    SDL_Rect button_rect;


    SDL_Texture *backg_texture;
    SDL_Texture *floor_texture;
    SDL_Texture *frontg_texture;
    
    t_character* player;
    t_character* enemy;
    t_game_card* cards[AMOUNT_OF_CARDS];
    t_button continue_button;
    bool player_action_av;
    int player_energy;


}               t_fightground;

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend, t_character* player);
int mx_render_fightground(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
void mx_clear_fightground(t_fightground *fg);
void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
void mx_handle_cards(t_fightground *fg);
bool mx_fight(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
void mx_clear_cards(t_game_card **cards);

#endif
