#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include<time.h>
#include<stdbool.h>


#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 900

typedef enum e_scenes {
    MENU,
    MAP,
    LEVEL
}            t_scenes;

typedef struct s_window_sdl {
    SDL_Window* window;
    SDL_Renderer* renderer;
    t_scenes scene;
    int cursor_x;
    int cursor_y;
    bool active;

}              t_window_sdl;


void mx_init_menu();
void mx_destroy(char* ms); 
SDL_Texture* mx_init_texture(char* path, SDL_Window* win, SDL_Renderer* renderer);




#endif
