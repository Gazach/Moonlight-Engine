#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace Window {

// Initialize SDL and create a window & renderer
bool Init(const std::string& title, int width, int height);

// Get the SDL_Window pointer
SDL_Window* GetWindow();

// Get the SDL_Renderer pointer
SDL_Renderer* GetRenderer();

// Destroy window and quit SDL
void Shutdown();

} // namespace Window
