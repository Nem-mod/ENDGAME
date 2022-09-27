#ifndef LEVEL_POINT_H
#define LEVEL_POINT_H

#include<stdbool.h>

typedef enum e_type {
    ENEMY,
    CHEST
    // TRADER,
    // RESTPOINT
} t_type;

typedef struct s_level_point
{
    bool active;
    t_type room;
    char* img_path;
    int x_dist;
    int y_dist;
    struct s_level_point *left;
    struct s_level_point *right;

}               t_level_point;


#endif
