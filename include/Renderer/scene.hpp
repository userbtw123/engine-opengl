#pragma once

#include "Core/logger.hpp"
#include "Renderer/camera.hpp"
#include "Renderer/game_object.hpp"
#include "Renderer/renderer.hpp"
#include "Renderer/shader.hpp"
#include <memory>
#include <string>
#include <vector>

class Scene {
  private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::string m_name;
    Camera m_camera;

  public:
    Shader* shader;
    Scene(const std::string& name, Shader& shader);

    const std::vector<std::shared_ptr<GameObject>>& getObjects() const { return m_objects; }

    void render(Renderer& renderer, Shader& shader);
    void update(float dt);

    void addObject(std::shared_ptr<GameObject> obj) {
        m_objects.push_back(obj);
        Logger::log(LogLevel::Info, "[Scene] Object {} added to scene '{}'", obj->name, m_name);
    }
};
