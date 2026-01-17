#include "Renderer/game_object.hpp"
#include <memory>

GameObject::GameObject(const std::string& name, std::shared_ptr<Mesh> mesh)
    : name(name), mesh(mesh) {
    transform.position = glm::vec3{0};
    transform.rotation = glm::vec3{0};
    transform.scale    = glm::vec3{1};
}
