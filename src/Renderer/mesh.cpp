#include "Renderer/mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    : indexCount(static_cast<uint32_t>(indices.size())) {
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);
    glCreateVertexArrays(1, &vao);

    glNamedBufferData(vbo, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glNamedBufferData(ebo, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glVertexArrayElementBuffer(vao, ebo);
    uint32_t bindingIndex = 0;

    glVertexArrayVertexBuffer(vao, bindingIndex, vbo, 0, sizeof(Vertex));
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
    glVertexArrayAttribBinding(vao, 0, bindingIndex);
}

void Mesh::bind() {
    glBindVertexArray(vao);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

uint32_t Mesh::getIndexCount() {
    return indexCount;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

std::shared_ptr<Mesh> Mesh::createCube() {
    std::vector<uint32_t> indices;
    std::vector<Vertex> vertices = {// Front face (Z+)
                                    {{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0, 0}},
                                    {{0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0, 0}},
                                    {{0.5f, 0.5f, 0.5f}, {0, 0, 1}, {1, 1, 0}},
                                    {{-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 1, 0}},
                                    // Back face (Z-)
                                    {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0, 0}},
                                    {{-0.5f, 0.5f, -0.5f}, {0, 0, -1}, {1, 1, 0}},
                                    {{0.5f, 0.5f, -0.5f}, {0, 0, -1}, {0, 1, 0}},
                                    {{0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 0, 0}},
                                    // Top face (Y+)
                                    {{-0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0, 1, 0}},
                                    {{-0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0, 0, 0}},
                                    {{0.5f, 0.5f, 0.5f}, {0, 1, 0}, {1, 0, 0}},
                                    {{0.5f, 0.5f, -0.5f}, {0, 1, 0}, {1, 1, 0}},
                                    // Bottom face (Y-)
                                    {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 0, 0}},
                                    {{0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0, 0}},
                                    {{0.5f, -0.5f, 0.5f}, {0, -1, 0}, {1, 1, 0}},
                                    {{-0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0, 1, 0}},
                                    // Right face (X+)
                                    {{0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 0, 0}},
                                    {{0.5f, 0.5f, -0.5f}, {1, 0, 0}, {1, 1, 0}},
                                    {{0.5f, 0.5f, 0.5f}, {1, 0, 0}, {0, 1, 0}},
                                    {{0.5f, -0.5f, 0.5f}, {1, 0, 0}, {0, 0, 0}},
                                    // Left face (X-)
                                    {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0, 0}},
                                    {{-0.5f, -0.5f, 0.5f}, {-1, 0, 0}, {1, 0, 0}},
                                    {{-0.5f, 0.5f, 0.5f}, {-1, 0, 0}, {1, 1, 0}},
                                    {{-0.5f, 0.5f, -0.5f}, {-1, 0, 0}, {0, 1, 0}}};

    // 6 faces, 2 triangles per face, 3 indices per triangle = 36 indices
    for (uint32_t i = 0; i < 6; ++i) {
        uint32_t offset = i * 4;
        indices.push_back(offset + 0);
        indices.push_back(offset + 1);
        indices.push_back(offset + 2);
        indices.push_back(offset + 2);
        indices.push_back(offset + 3);
        indices.push_back(offset + 0);
    }

    return std::make_shared<Mesh>(vertices, indices);
}
