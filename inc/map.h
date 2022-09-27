#ifndef MAP_H
#define MAP_H

#include<stdbool.h>
#include "level_point.h"


typedef struct s_map
{
    SDL_Texture *tex;
    char* img_path;
    bool active;
    SDL_Rect rectimg;
    SDL_Rect rectdist;

    t_level_point *start_point;

}               t_map;


t_map mx_create_map(SDL_Window* win, SDL_Renderer* renderer);
void mx_render_map(t_map *map, SDL_Renderer *renderer);
void mx_clear_map(t_map *map);

void mx_generate_points();
void mx_clear_points(t_map *map);
void mx_handle_map(t_map *map, SDL_Window* win, SDL_Renderer* renderer);

#endif
