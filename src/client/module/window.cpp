#include "window.hpp"
#include <iostream>

namespace Window {

static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;

bool Init(const std::string& title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(
            title.c_str(),
            width, height,
            SDL_WINDOW_RESIZABLE,   // flags: resizable window
            &gWindow,
            &gRenderer))
    {
        std::cerr << "SDL_CreateWindowAndRenderer failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    return true;
}

SDL_Window* GetWindow() {
    return gWindow;
}

SDL_Renderer* GetRenderer() {
    return gRenderer;
}

void Shutdown() {
    if (gRenderer) SDL_DestroyRenderer(gRenderer);
    if (gWindow) SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

} // namespace Window
