#pragma once

#include "Renderer/mesh.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <memory>
#include <string>

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 getTransformMatrix() {
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, position);
        model           = glm::rotate(model, glm::radians(rotation.x), {1, 0, 0});
        model           = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});
        model           = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
        model           = glm::scale(model, scale);
        return model;
    }
};

class GameObject {
  public:
    Transform transform;
    std::string name;
    std::shared_ptr<Mesh> mesh;
    GameObject(const std::string& name, std::shared_ptr<Mesh>);
};
