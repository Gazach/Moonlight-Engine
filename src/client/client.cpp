#include "client.hpp"
#include "module/window.hpp"
#include <SDL3/SDL.h>

int RunClient() {
    if (!Window::Init("Moonlight Engine", 1280, 720)) {
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

        SDL_SetRenderDrawColor(Window::GetRenderer(), 20, 20, 20, 255); // dark gray background
        SDL_RenderClear(Window::GetRenderer());

        // TODO: Render engine/editor stuff here

        SDL_RenderPresent(Window::GetRenderer());
    }

    Window::Shutdown();
    return 0;
}
