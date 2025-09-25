#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace Window {

bool Init(const std::string& title, int width, int height);
SDL_Window* GetWindow();
SDL_GLContext GetContext();
void Clear(float fr, float fg, float fb, float fa);
void Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void Present();
void Shutdown();

} // namespace Window
