#ifndef ROOM_H
#define ROOM_H
#include "window_sdl.h"
#include "character.h"
#include "button.h"
#include "level_point.h"

typedef struct  s_room {
    char *background_path;
    char *floor_path;
    char *frontground_path;

    SDL_Rect backg_rect;
    SDL_Rect floor_rect;
    SDL_Rect frontg_rect;

    SDL_Rect player_rect;
    t_button room_obj;

    SDL_Texture *backg_texture;
    SDL_Texture *floor_texture;
    SDL_Texture *frontg_texture;
    
    t_character* player;


}               t_room;

t_room *mx_create_room(SDL_Window *win, SDL_Renderer *rend,
                     t_character* player, int type);
void mx_render_room(t_room *room, SDL_Renderer *rend);
void mx_clear_room(t_room *room);
int mx_handle_room(t_room *room);

#endif
