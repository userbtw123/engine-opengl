#include "Renderer/renderer.hpp"
#include <glad/glad.h>

Renderer::Renderer() {}

void Renderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
