#ifndef FIGHTGROUND_H
#define FIGHTGROUND_H

#include "window_sdl.h"
#include "character.h"
#include "inventory.h"
#include "game_card.h"
#include "button.h"

#define AMOUNT_OF_CARDS 5
#define AMOUNT_OF_ENERGY 3
#define CARDS_TO_CHOOSE_AMOUNT 3
#define P_OF_ENEMYS 3

typedef struct  s_fightground {
    char *background_path;
    char *floor_path;
    char *frontground_path;
    char *button_path;
    char *dm_path;
    char *bag_path;

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
    t_inventory *inv;

    int discard_cards_count;
    bool player_action_av;
    bool exit_flag;
    bool win_flag;
    int player_energy;


}               t_fightground;

t_fightground *mx_create_fightground(SDL_Window *win, SDL_Renderer *rend, t_character* player, t_inventory *inv);
int mx_render_fightground(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
void mx_clear_fightground(t_fightground **fg);
void mx_create_cards(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg, int cards_ammount);
void mx_handle_cards(t_fightground *fg, SDL_Window *win, SDL_Renderer *rend);
void mx_fight(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);
void mx_update_fight_bars(t_fightground *fg);
void mx_clear_cards(t_game_card **cards);
void mx_win_level(SDL_Window *win, SDL_Renderer *rend, t_fightground* fg);

#endif
