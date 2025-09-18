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

// Clear the window with a color
void Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Present the rendered content to the window
void Present();

// Destroy window and quit SDL
void Shutdown();

} // namespace Window
