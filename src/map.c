#include "../inc/window_sdl.h"
#include "../inc/map.h"

t_map mx_create_map(SDL_Window* win, SDL_Renderer* renderer) {
    t_map map;
    map.active = true;
    map.img_path = "resource/img/map.png";
    map.tex = mx_init_texture(map.img_path, win, renderer);
    map.start_point = mx_create_lp(win, renderer);
    map.rectdist.h = WINDOW_HEIGHT;
    map.rectdist.w = WINDOW_WIDTH ;
    map.rectdist.x = WINDOW_WIDTH / 2;
    map.rectdist.y = WINDOW_HEIGHT / 4;
    mx_generate_points(&map, win, renderer);
    return map;
}

void mx_render_map(t_map *map, SDL_Renderer *renderer) {

    // draw the image to the window
    SDL_RenderCopy(renderer, map->tex, NULL, &map->rectdist);

    t_level_point *temp = map->start_point;
    while (temp->next != NULL) {
        mx_render_lp(temp, renderer);
        temp = temp->next;
    }
}

void mx_clear_map(t_map *map) {
    SDL_DestroyTexture(map->tex);
}



void mx_generate_points(t_map *map, SDL_Window* win, SDL_Renderer* renderer) {
    srand(time(NULL));
    int amount = rand() % 4 + 7;
    t_level_point* temp_point = mx_create_lp(win, renderer);
    t_level_point* current_point = temp_point;
    map->start_point = mx_create_lp(win, renderer);
    map->start_point->next = current_point;

    map->start_point->active = true;
    map->start_point->next = current_point;

    for (int i = 0; i < amount; i++) {
        temp_point = mx_create_lp(win, renderer);
        temp_point->rect.y -= (i + 1) * 900 / amount;
        current_point->next = temp_point;
        current_point = temp_point;
    }
}

void mx_clear_points(t_map *map) {
    while (map->start_point->next != NULL) {
        t_level_point* temp = map->start_point->next;
        mx_clear_lp(map->start_point);
        map->start_point = temp;
    }
}
