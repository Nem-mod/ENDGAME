#include "../inc/window_sdl.h"
#include "../inc/map.h"

t_map mx_create_map() {
    t_map map;
    map.active = true;
    map.img_path = "resource/img/map.jpg";
    map.start_point = mx_create_lp();
    // mx_generate_points(map);
    return map;
}

void mx_render_map(t_map *map, SDL_Renderer *renderer) {

    map->tex = mx_init_texture(map->img_path);
    SDL_Rect rect;
    rect.h = 300 * 4;
    rect.w = 300 * 3;
    rect.x = 0;
    rect.y = 0;
    // draw the image to the window
    SDL_RenderCopy(renderer, map->tex, &rect, NULL);

    t_level_point *temp = map->start_point;
    while (temp->next != NULL) {
        mx_render_lp(temp, renderer);
        temp = temp->next;
    }
    // tex = mx_init_texture("resource/img/second.png");
}

void mx_clear_map(t_map *map) {
    SDL_DestroyTexture(map->tex);

}



void mx_generate_points(t_map *map) {
    srand(time(NULL));
    int amount = rand() % 4 + 7;
    t_level_point* temp_point = mx_create_lp();
    t_level_point* current_point = temp_point;
    map->start_point = mx_create_lp();
    map->start_point->next = current_point;

    map->start_point->active = true;
    map->start_point->next = current_point;

    for (int i = 0; i < amount; i++) {
        temp_point = mx_create_lp();
        temp_point->rect.y -= (i + 1) * 900 / amount;
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
