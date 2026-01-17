#pragma once

#include "Renderer/game_object.hpp"
#include "Renderer/shader.hpp"
#include <memory>
#include <string>
#include <vector>

class Scene {
  public:
    std::string name;
    std::shared_ptr<Shader> shader;
    Scene(const std::string& name, std::shared_ptr<Shader> shader);
    std::vector<GameObject> objects;
    void render();
};
