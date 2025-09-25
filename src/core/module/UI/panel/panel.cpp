#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <string>
#include "../client/module/window.hpp"
#include "panel.hpp"

// A simple shader for solid colors
static const char* vsSource = R"(
#version 460 core
layout (location = 0) in vec2 aPos;
uniform vec2 uResolution;
uniform vec2 uPosition;
uniform vec2 uSize;

void main() {
    // Convert from pixel space -> NDC
    vec2 pos = aPos * uSize + uPosition;
    vec2 ndc = (pos / uResolution) * 2.0 - 1.0;
    ndc.y = -ndc.y; // flip Y for screen coordinates
    gl_Position = vec4(ndc, 0.0, 1.0);
}
)";

static const char* fsSource = R"(
#version 460 core
out vec4 FragColor;
uniform vec4 uColor;
void main() {
    FragColor = uColor;
}
)";

static GLuint shader = 0;
static GLuint vao = 0, vbo = 0;

// Initialize once
static void InitGLObjects() {
    if (shader != 0) return; // already created

    // Compile shaders
    auto compileShader = [](GLenum type, const char* src) -> GLuint {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        return s;
    };

    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    // Quad (two triangles) in [0,1] space
    float vertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

// Draw a rectangle
static void DrawQuad(float x, float y, float w, float h,
                     const SDL_Color& color,
                     int windowW, int windowH) {
    InitGLObjects();
    glUseProgram(shader);

    // uniforms
    GLint uResolution = glGetUniformLocation(shader, "uResolution");
    GLint uPosition   = glGetUniformLocation(shader, "uPosition");
    GLint uSize       = glGetUniformLocation(shader, "uSize");
    GLint uColor      = glGetUniformLocation(shader, "uColor");

    glUniform2f(uResolution, (float)windowW, (float)windowH);
    glUniform2f(uPosition,  (float)x, (float)y);
    glUniform2f(uSize,      (float)w, (float)h);
    glUniform4f(uColor,
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// overload: draw rect with SDL_Color
int Panel(int posX, int posY, int width, int height,
          SDL_Color color, const PanelOptions& opt) {
    int windowW, windowH;
    SDL_GetWindowSize(Window::GetWindow(), &windowW, &windowH);

    if (width == STRETCH) width  = windowW - posX;
    if (height == STRETCH) height = windowH - posY;

    // Border first
    if (opt.border.isEnabled) {
        int t = opt.border.thickness;
        int newW = width + t * 2;
        int newH = height + t * 2;
        DrawQuad((float)(posX - t), (float)(posY - t),
                 (float)newW, (float)newH,
                 opt.border.color, windowW, windowH);
    }

    // Fill rect
    DrawQuad((float)posX, (float)posY,
             (float)width, (float)height,
             color, windowW, windowH);

    return 0;
}

// overload: draw rect with hex color
int Panel(int posX, int posY, int width, int height,
          const std::string& hex, const PanelOptions& opt) {
    SDL_Color color = HexToColor(hex);
    return Panel(posX, posY, width, height, color, opt);
}
