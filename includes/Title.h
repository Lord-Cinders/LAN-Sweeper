#pragma once

#include <SDL2/SDL.h>
#include "Screen.h"

class Title : public virtual Screen {
    public:
        Title(SDL_Window * g_window, SDL_Renderer * g_renderer);    
        void Draw(int w, int h) override;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};