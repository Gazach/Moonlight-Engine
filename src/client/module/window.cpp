// include glad BEFORE SDL's GL headers in the translation unit to avoid header-order problems
#include <glad/glad.h>
#include <iostream>
#include "window.hpp"
#include <SDL3/SDL.h>

namespace Window {

static SDL_Window*    gWindow  = nullptr;
static SDL_GLContext  gContext = nullptr;

bool Init(const std::string& title, int width, int height) {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create an OpenGL-capable window
    gWindow = SDL_CreateWindow(title.c_str(),
                               width, height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!gWindow) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    gContext = SDL_GL_CreateContext(gWindow);
    if (!gContext) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed\n";
        SDL_GL_DestroyContext(gContext);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return false;
    }

    std::cout << "OpenGL: " << (const char*)glGetString(GL_VERSION) << "\n";
    return true;
}

SDL_Window* GetWindow() {
    return gWindow;
}

SDL_GLContext GetContext() {
    return gContext;
}

void Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush(); // force immediate draw (optional)
}

void Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    Clear(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void Present() {
    SDL_GL_SwapWindow(gWindow);
}

void Shutdown() {
    if (gContext) SDL_GL_DestroyContext(gContext);
    if (gWindow)  SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

} // namespace Window
