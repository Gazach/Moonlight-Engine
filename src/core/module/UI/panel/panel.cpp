#include <SDL3/SDL.h>

#include <string>

#include "../client/module/window.hpp"
#include "../helper/Color.hpp"
#include "panel.hpp"

// overload: draw rect with SDL_Color
int Panel(int posX, int posY, int width, int height, SDL_Color color) {

    int windowW, windowH;
    SDL_GetCurrentRenderOutputSize(Window::GetRenderer(), &windowW, &windowH);

    if (width == STRETCH) {
        width = windowW - posX;
    }
    if (height == STRETCH) {
        height = windowH - posY;
    }


    SDL_FRect rect = { float(posX), float(posY), float(width), float(height) };
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
    return SDL_RenderFillRect(Window::GetRenderer(), &rect);
}

// overload: draw rect with hex color
int Panel(int posX, int posY, int width, int height, const std::string& hex) {
    SDL_Color color = HexToColor(hex);
    return Panel(posX, posY, width, height, color);
}