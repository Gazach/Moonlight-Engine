#include <SDL3/SDL.h>

#include <string>

#include "../client/module/window.hpp"
#include "panel.hpp"



// overload: draw rect with SDL_Color
int Panel(int posX, int posY, int width, int height,
          SDL_Color color, const PanelOptions& opt) {

    // Get current window size
    int windowW, windowH;
    SDL_GetCurrentRenderOutputSize(Window::GetRenderer(), &windowW, &windowH);
    // if width or height is STRETCH, make it stretch to window size
    if (width == STRETCH) {
        width = windowW - posX;
    }
    if (height == STRETCH) {
        height = windowH - posY;
    }

    if (opt.border.isEnabled) {
        // get border thickness and calculate new rect size
        int thickness = opt.border.thickness;
        int newborderwidth = width + thickness * 2;
        int newborderheight = height + thickness * 2;

        SDL_FRect borderRect = { float(posX - thickness), float(posY - thickness), float(newborderwidth), float(newborderheight) }; //get rect values
        
        SDL_SetRenderDrawColor(Window::GetRenderer(), opt.border.color.r, opt.border.color.g, opt.border.color.b, opt.border.color.a);
        SDL_RenderFillRect(Window::GetRenderer(), &borderRect); //draw border rect

    }

    SDL_FRect rect = { float(posX), float(posY), float(width), float(height) };
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
    return SDL_RenderFillRect(Window::GetRenderer(), &rect);
}

// overload: draw rect with hex color
int Panel(int posX, int posY, int width, int height,
     const std::string& hex, const PanelOptions& opt) {
    SDL_Color color = HexToColor(hex);
    return Panel(posX, posY, width, height, color, opt);
}