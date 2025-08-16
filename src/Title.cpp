#include "Title.h"
#include <iostream>

Title::Title(SDL_Window *g_window, SDL_Renderer *g_renderer) {
    window = g_window;
    renderer = g_renderer;
}

void Title::Draw(int w, int h) {
    clear_screen(renderer);
    std::cout << "Hello World" << std::endl;
}