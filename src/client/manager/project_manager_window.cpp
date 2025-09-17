#include "../module/window.hpp"
#include <SDL3/SDL.h>
#include "../../core/module/UI/panel/panel.hpp"

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

        Panel(20, 20, 200, 100, "#ff3939ff", 
            PanelOptions()
            .SetBorderOptions(PanelBorderOptions()
            .SetEnabled(true)
            .SetThickness(3)
            .SetColor("#ffffffff")
        ));
        
        SDL_RenderPresent(Window::GetRenderer());
    }

    Window::Shutdown();
    return 0;
}