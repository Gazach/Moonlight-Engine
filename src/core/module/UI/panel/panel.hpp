#pragma once
#include <SDL3/SDL.h>
#include <string>

constexpr int STRETCH = -1;

int Panel(int posX, int posY, int width, int height, SDL_Color color);

int Panel(int posX, int posY, int width, int height, const std::string& hex);