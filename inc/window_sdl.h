#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <stdbool.h>
#include "button.h"

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1200
#define CLOSE_MENU 999

typedef enum e_scenes {
    MENU,
    MAP,
    LEVEL,
    DEATH,
    EXIT,
    ROOM,
    RESTART,
    BOSSFIGHT,
    VICTORY,
    TUTORIAL
}            t_scenes;

typedef struct s_window_sdl {
    char *music_path;
    Mix_Music *bg_music;
    SDL_Window* window;
    SDL_Renderer* renderer;
    t_scenes scene;
    int cursor_x;
    int cursor_y;
    bool active;
    bool menu;
}              t_window_sdl;

SDL_Texture* mx_init_texture(char* path, SDL_Window* win, SDL_Renderer* renderer);

#endif
