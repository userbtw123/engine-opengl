#include "Renderer/renderer.hpp"
#include <glad/glad.h>

Renderer::Renderer() : background_color(0.2, 0.2, 0.2) {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::clear(float* rgb) {
    glClearColor(rgb[0], rgb[1], rgb[2], 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setPolygonMode(GLenum mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}
