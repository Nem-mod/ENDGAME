#include "../inc/room.h"

t_room *mx_create_room(SDL_Window *win, SDL_Renderer *rend,
t_character* player, int type) {
    t_room *room = malloc(sizeof(*room));

    room->background_path = "resource/img/fight/background.jfif";
    room->floor_path = "resource/img/fight/floor.jpg";
    room->frontground_path = "resource/img/fight/column.png";

    room->backg_rect.x = 0;
    room->backg_rect.y = 0;
    room->backg_rect.h = WINDOW_HEIGHT / 1.5;
    room->backg_rect.w = WINDOW_WIDTH;
    room->backg_texture = mx_init_texture(room->background_path, win, rend);

    room->floor_rect.x = 0;
    room->floor_rect.y = WINDOW_HEIGHT / 1.5;
    room->floor_rect.h = WINDOW_HEIGHT / 4;
    room->floor_rect.w = WINDOW_WIDTH;
    room->floor_texture = mx_init_texture(room->floor_path, win, rend);

    room->frontg_rect.x = 0;
    room->frontg_rect.y = 0;
    room->frontg_rect.h = WINDOW_HEIGHT / 1.5;
    room->frontg_rect.w = WINDOW_WIDTH;
    room->frontg_texture = mx_init_texture(room->frontground_path, win, rend);

    room->player_rect.h = 300;
    room->player_rect.w = 300;
    room->player_rect.x = 150;
    room->player_rect.y = WINDOW_HEIGHT / 1.5 - 200;
    room->player = player;

    if (type == CHEST) {
        room->room_obj = mx_create_button(200, 200, 850, WINDOW_HEIGHT / 1.5 - 100, 
        "resource/img/chest.png");
        room->room_obj.tex = mx_init_texture(room->room_obj.img_path, win, rend);
    }
    return room;
}

void mx_render_room(t_room *room, SDL_Renderer *rend) {
    SDL_RenderCopy(rend, room->backg_texture, NULL, &room->backg_rect);

    SDL_RenderCopy(rend, room->floor_texture, NULL, &room->floor_rect);
    SDL_RenderCopy(rend, room->frontg_texture, NULL, &room->frontg_rect);

    mx_render_character(room->player, rend, room->player_rect);
    SDL_RenderCopy(rend, room->room_obj.tex, NULL, &room->room_obj.d_rect);
}

int mx_handle_room(t_room *room) {
    if (mx_handle_button(room->room_obj.d_rect)) {
        return MAP;
    }
    return ROOM;
}

void mx_clear_room(t_room *room) {
    SDL_DestroyTexture(room->backg_texture);
    SDL_DestroyTexture(room->floor_texture);
    SDL_DestroyTexture(room->frontg_texture);
    free(room);
    room = NULL;
}
