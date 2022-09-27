#ifndef LEVEL_POINT_H
#define LEVEL_POINT_H

#include<stdbool.h>
typedef struct s_level_point
{
    bool active;
    char* img_path;
    int x_dist;
    int y_dist;
}               t_level_point;


#endif
