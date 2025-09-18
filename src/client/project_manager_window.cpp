#include "module/window.hpp"
#include <SDL3/SDL.h>
#include <lua.hpp>

int OpenProjectManager(lua_State* L) {
    if (!Window::Init("Moonlight Engine | Project Manager", 1280, 720)) {
        return -1;
    }

    bool running = true;
    SDL_Event event;

    // Load the Project Manager lua script
    if (luaL_dofile(L, "project_manager.lua") != LUA_OK) {
        printf("Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Clear window
        Window::Clear(55, 55, 55, 255);

        // Call Lua "UpdateUI()" every frame
        lua_getglobal(L, "UpdateUI");
        if (lua_isfunction(L, -1)) {
            if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                printf("Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        } else {
            lua_pop(L, 1); 
        }

        // Present window
        Window::Present();
    }

    Window::Shutdown();
    return 0;
}