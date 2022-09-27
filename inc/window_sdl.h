#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


void mx_init_menu();
void mx_destroy(char* ms); 
SDL_Texture* mx_init_texture(char* path);

SDL_Window* win;
SDL_Renderer* w_render;

#endif
