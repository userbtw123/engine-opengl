#pragma once

#include <string>
#include "Renderer/renderer.hpp"
#include "Renderer/scene.hpp"
#include <vector>
#include "Core/window.hpp"

class Engine {
  public:
    Window window;
    Shader shader;
    Renderer renderer;
    DebugOverlay debugOverlay;

    std::vector<std::unique_ptr<Scene>> scenes;
    Scene* current_scene = nullptr;

    Engine(const std::string& title, int width, int height);
    ~Engine();
    int run();
};
