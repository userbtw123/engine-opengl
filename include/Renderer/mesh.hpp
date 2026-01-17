#pragma once

#include <cstdint>
#include <vector>
#include <memory>

struct Vertex {
    float pos[3];
    float normal[3];
    float uv[3];
};

class Mesh {
  private:
    uint32_t vbo, ebo, vao;
    uint32_t indexCount;

  public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~Mesh();

    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;

    void bind();
    void unbind();

    uint32_t getIndexCount();

    static std::shared_ptr<Mesh> createCube();
};
