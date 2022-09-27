#ifndef MAP_H
#define MAP_H

#include<stdbool.h>
#include "level_point.h"


typedef struct s_map
{
    SDL_Texture *tex;
    char* img_path;
    bool active;

    t_level_point *level;

}               t_map;



t_map mx_create_map();
void mx_render_map(t_map *map);
void mx_clear_map(t_map *map);


#endif
