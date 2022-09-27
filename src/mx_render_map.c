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
    // tex = mx_init_texture("resource/img/second.png");
}

void mx_clear_map(t_map *map) {
    SDL_DestroyTexture(map->tex);

}
