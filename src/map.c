#include "../inc/window_sdl.h"
#include "../inc/map.h"

t_map mx_create_map(SDL_Window* win, SDL_Renderer* renderer) {
    t_map map;
    map.active = true;
    map.img_path = "resource/img/map.png";
    map.tex = mx_init_texture(map.img_path, win, renderer);
    map.start_point = mx_create_lp(win, renderer);
    map.rectdist.h = WINDOW_HEIGHT;
    map.rectdist.w = WINDOW_WIDTH;
    map.rectdist.x = 0;
    map.rectdist.y = 0;
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
    int amount = rand() % 3 + 4;
    t_level_point* temp_point = mx_create_lp(win, renderer);
    t_level_point* current_point = temp_point;
    map->start_point = mx_create_lp(win, renderer);
    map->start_point->rect.x = WINDOW_WIDTH - 200;
    map->start_point->rect.y = WINDOW_HEIGHT - 200;
    
    map->start_point->active = true;
    SDL_DestroyTexture(map->start_point->tex);
    map->start_point->tex = mx_init_texture("resource/img/mob.png", win, renderer);
    current_point->rect.x = WINDOW_WIDTH - 350;
    current_point->rect.x = WINDOW_HEIGHT - 350;

    map->start_point->next = current_point;

    // map->start_point->active = true;

    for (int i = 0; i < amount; i++) {

        temp_point = mx_create_lp(win, renderer);
        temp_point->rect.y -= 300 + (i + 1) * (WINDOW_HEIGHT - 400) / (amount + 2);
        current_point->next = temp_point;
        temp_point->rect.x -= -100 + i * (WINDOW_WIDTH - 400) / (amount + 2);
        if (i == 1) {
            temp_point->rect.y = WINDOW_HEIGHT - 400;
            temp_point->rect.x = WINDOW_WIDTH - 400;
        }
        if (i == amount - 2) {
            temp_point->rect.y = 250; 
            temp_point->rect.x = 250;
        }
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

void mx_handle_map(t_map *map, SDL_Window* win, SDL_Renderer* renderer){
    t_level_point* temp = map->start_point;
    while (temp->next != NULL)
    {
        mx_handle_point_level(temp, win, renderer);
        temp = temp->next;
    }
    
}

