#pragma once

#include <glad/glad.h>
#include "glm/ext/vector_float3.hpp"

class Renderer {
  public:
    glm::vec3 background_color;
    Renderer();

    void render();

    void clear(float r, float g, float b);
    void clear(float* rgb);

    void setPolygonMode(GLenum mode);
};
