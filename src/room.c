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

    room->exit_btn = mx_create_button(150, 50, WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT - 100,
                                        "resource/img/button-finish.png");
    room->exit_btn.tex = mx_init_texture(room->exit_btn.img_path, win, rend);


    if (type == CHEST) {
        room->chest_drop = 1;
        room->room_obj = mx_create_button(200, 200, 850, WINDOW_HEIGHT / 1.5 - 100, 
                                            "resource/img/chest_def.png");
        room->room_obj.tex = mx_init_texture(room->room_obj.img_path, win, rend);
    }

    room->treasure = mx_create_potion(win, rend);
    room->treasure->rect.x = 950;
    room->treasure->rect.y = WINDOW_HEIGHT / 1.5 - 200;
    room->chest_drop_f = false;
    return room;
}

int mx_render_room(t_room *room, SDL_Renderer *rend, t_potion_bar *potion_bar, SDL_Window *win) {
   
    SDL_RenderCopy(rend, room->backg_texture, NULL, &room->backg_rect);

    SDL_RenderCopy(rend, room->floor_texture, NULL, &room->floor_rect);
    SDL_RenderCopy(rend, room->frontg_texture, NULL, &room->frontg_rect);

    mx_render_character(room->player, rend, room->player_rect);
    SDL_RenderCopy(rend, room->exit_btn.tex, NULL, &room->exit_btn.d_rect);
    SDL_RenderCopy(rend, room->room_obj.tex, NULL, &room->room_obj.d_rect);

    if (mx_handle_button(room->room_obj.d_rect) && room->chest_drop == 1) {
        room->room_obj.img_path = "resource/img/chest_def2.png";
        SDL_DestroyTexture(room->room_obj.tex);
        room->room_obj.tex = mx_init_texture(room->room_obj.img_path, win, rend);
        room->chest_drop_f = true;

        
    }
    if(room->chest_drop_f) {
        SDL_RenderCopy(rend, room->treasure->tex, NULL, &room->treasure->rect);
        if(mx_handle_button(room->treasure->rect)) {
            room->chest_drop = 0;
            if(potion_bar->potions_count < MAX_AMOUNT_OF_PT)
                potion_bar->potions_count += 1;
        }
    }

    if (mx_handle_button(room->exit_btn.d_rect)) {
        return MAP;
    }
    return ROOM;
}

int mx_handle_room(t_room *room, t_potion_bar *potion_bar) {
    if (mx_handle_button(room->room_obj.d_rect)) {
        room->room_obj.img_path = "resource/img/chest_def2.png";

        potion_bar->potions_count += 1;
        SDL_Delay(1000);
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
