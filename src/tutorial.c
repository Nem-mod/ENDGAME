#include "../inc/tutorial.h"

t_tutorial* mx_create_tutorial(SDL_Window* win, SDL_Renderer* renderer) {
    t_tutorial *tutorial = malloc(sizeof(t_tutorial));
    tutorial->rect.h = WINDOW_HEIGHT;
    tutorial->rect.w = WINDOW_WIDTH;
    tutorial->rect.x = 0;
    tutorial->rect.y = 0;
    tutorial->textures[0] = mx_init_texture("resource/img/tutorial1.png", win, renderer);
    tutorial->textures[1] = mx_init_texture("resource/img/tutorial2.png", win, renderer);
    tutorial->textures[2] = mx_init_texture("resource/img/tutorial3.png", win, renderer);
    tutorial->textures[3] = mx_init_texture("resource/img/tutorial4.png", win, renderer);
    tutorial->textures[4] = mx_init_texture("resource/img/tutorial5.png", win, renderer);
    tutorial->slide = 0;
    return tutorial;
}
t_scenes mx_render_tutorial(t_tutorial *tutorial, SDL_Renderer *renderer){
    if(tutorial->slide < SLIDES){
        SDL_RenderCopy(renderer, tutorial->textures[tutorial->slide], NULL, &tutorial->rect);
        SDL_Delay(50);
        if(mx_handle_button(tutorial->rect)) {
            SDL_RenderPresent(renderer);
            tutorial->slide++;
            SDL_Delay(500);

        }
        return TUTORIAL;
    } else {
        return MENU;

    }
}
void mx_clear_tutorial(t_tutorial *tutorial) {
    for (int i = 0; i < SLIDES; i++) {
        SDL_DestroyTexture(tutorial->textures[i]);
    }
    free(tutorial);
    tutorial = NULL;
    
}
