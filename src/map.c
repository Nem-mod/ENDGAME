#include "../inc/window_sdl.h"
#include "../inc/map.h"

t_map mx_create_map() {
    t_map map;
    map.active = true;
    map.img_path = "resource/img/map.png";

    return map;
}

void mx_render_map(t_map *map) {

    map->tex = mx_init_texture(map->img_path);
    SDL_Rect rect;
    rect.h = 300 * 4;
    rect.w = 300 * 3;
    rect.x = 100;
    rect.y = -100;
    // draw the image to the window
    SDL_RenderCopy(w_render, map->tex, &rect, NULL);
    mx_generate_points(&map);
    
    
    // tex = mx_init_texture("resource/img/second.png");
}

void mx_clear_map(t_map *map) {
    SDL_DestroyTexture(map->tex);

}



void mx_generate_points(t_map *map) {
    int amount = rand() % 5;
    map->start_point = mx_create_lp();
    t_level_point* temp_point = mx_create_lp();
    t_level_point* current_point = temp_point;
    map->start_point->active = true;
    map->start_point->next = current_point;

    for (int i = 0; i < amount; i++) {
        temp_point = mx_create_lp();
        current_point->next = temp_point;
        current_point = temp_point;
    }
}

void mx_clear_points(t_map *map) {
    while (map->start_point->next != NULL) {
        t_level_point* temp = map->start_point->next;
        free(map->start_point);
        map->start_point = temp;
    }
}
