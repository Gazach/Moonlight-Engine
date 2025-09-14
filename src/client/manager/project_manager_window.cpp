#include "../module/window.hpp"
#include <SDL3/SDL.h>
#include "../../core/render/drawshapes.hpp"

int OpenProjectManager() {
    if (!Window::Init("Moonlight Engine | Project Manager", 1280, 720)) {
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        DrawRect(20, 20, 100, 50, "#151515ff");
        SDL_RenderClear(Window::GetRenderer());

        DrawRect(0, 0, 100, 2000, "#ff4646ff");

        SDL_RenderPresent(Window::GetRenderer());
    }

    Window::Shutdown();
    return 0;
}