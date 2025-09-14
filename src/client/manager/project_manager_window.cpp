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

        DrawRect(20, 20, 100, 50, "#1e1e1eff");
        SDL_RenderClear(Window::GetRenderer());

        DrawRect(0, 0, STRETCH, 50, "#151515ff");
        DrawRect(0, 51, STRETCH, 1, "#434343ff");
        DrawRect(0, 52, 320, STRETCH, "#151515ff");
        DrawRect(321, 52, 1, STRETCH, "#434343ff");
        SDL_RenderPresent(Window::GetRenderer());
    }

    Window::Shutdown();
    return 0;
}