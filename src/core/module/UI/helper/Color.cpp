#include "Color.hpp"
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