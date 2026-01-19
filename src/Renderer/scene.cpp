#include "Renderer/scene.hpp"
#include "Renderer/shader.hpp"

Scene::Scene(const std::string& name, Shader& shader) : m_name(name), shader(&shader) {}
void Scene::render(Renderer& renderer, Shader& shader) {} // TODO: implement the method
