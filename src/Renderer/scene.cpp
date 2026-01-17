#include "Renderer/scene.hpp"
#include "Renderer/shader.hpp"
#include <memory>

Scene::Scene(const std::string& name, std::shared_ptr<Shader> shader)
    : name(name), shader(shader) {}
void Scene::render() {
    for (auto& obj : objects) {
        obj.mesh->bind();
        shader->setUniform("model", obj.transform.getTransformMatrix());
        glDrawElements(GL_TRIANGLES, obj.mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
    }
}
