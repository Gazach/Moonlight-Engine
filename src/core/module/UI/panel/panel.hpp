#pragma once
#include <SDL3/SDL.h>
#include <string>

#include "../helper/Color.hpp"

// option to add border to a panel
struct PanelBorderOptions {
    bool isEnabled = false;
    int thickness = 1;
    SDL_Color color = { 0, 0, 0, 255 };

    PanelBorderOptions& SetEnabled(bool enabled) {
        isEnabled = enabled;
        return *this;
    }
    PanelBorderOptions& SetThickness(int t) {
        thickness = t;
        return *this;
    }
    PanelBorderOptions& SetColor(const SDL_Color& c) {
        color = c;
        return *this;
    }
    PanelBorderOptions& SetColor(const std::string& hex) {
        color = HexToColor(hex);
        return *this;
    }
};

struct PanelOptions {
    PanelBorderOptions border;

    PanelOptions& SetBorderOptions(const PanelBorderOptions& b) {
        border = b;
        return *this;
    }
};

// Use -1 for width or height to make it stretch to the window size
constexpr int STRETCH = -1;
// overloads for Panel function
int Panel(int posX, int posY, int width, int height, SDL_Color color, const PanelOptions& opt = {});

int Panel(int posX, int posY, int width, int height, const std::string& hex, const PanelOptions& opt = {});