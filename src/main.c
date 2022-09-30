#include "../inc/main.h"

int main() {
    
    t_window_sdl *gameWindow = mx_init_SDL2();
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT,2,2048);
    gameWindow->bg_music = Mix_LoadMUS("resource/audio/song.mp3");
    Mix_PlayMusic(gameWindow->bg_music, -1);
    

    mx_init_game(gameWindow);
    SDL_RenderClear(gameWindow->renderer);
    SDL_DestroyRenderer(gameWindow->renderer);
    Mix_FreeMusic(gameWindow->bg_music);
   
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
