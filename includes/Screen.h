#pragma once

#include <SDL2/SDL.h>

struct SDL_Renderer;

class Screen{
    public:
        virtual void Draw(int w, int h) = 0;
        
        void clear_screen(SDL_Renderer * renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
};