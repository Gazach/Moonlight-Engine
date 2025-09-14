#include <SDL3/SDL.h>
#include "../client/module/window.hpp"
#include <string>
#include <stdexcept>

// helper: convert "#RRGGBB" or "#RRGGBBAA" to SDL_Color
SDL_Color HexToColor(const std::string& hex) {
    if (hex.size() != 7 && hex.size() != 9) {
        throw std::invalid_argument("Hex must be #RRGGBB or #RRGGBBAA");
    }

    auto hexToInt = [](const std::string& h) {
        return static_cast<Uint8>(std::stoi(h, nullptr, 16));
    };

    Uint8 r = hexToInt(hex.substr(1, 2));
    Uint8 g = hexToInt(hex.substr(3, 2));
    Uint8 b = hexToInt(hex.substr(5, 2));
    Uint8 a = (hex.size() == 9) ? hexToInt(hex.substr(7, 2)) : 255;

    return SDL_Color{r, g, b, a};
}

// overload: draw rect with SDL_Color
int DrawRect(int posX, int posY, int width, int height, SDL_Color color) {
    SDL_FRect rect = { float(posX), float(posY), float(width), float(height) };
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
    return SDL_RenderFillRect(Window::GetRenderer(), &rect);
}

// overload: draw rect with hex color
int DrawRect(int posX, int posY, int width, int height, const std::string& hex) {
    SDL_Color color = HexToColor(hex);
    return DrawRect(posX, posY, width, height, color);
}