#pragma once

#include "Core/debugOverlay.hpp"

#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>
#include <string>

struct GlfwWindowDeleter {
    void operator()(GLFWwindow* window) const {
        if (window) {
            glfwDestroyWindow(window);
        }
    }
};

class Window {
  public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    bool isOpen();
    void swapBuffers();
    void poolEvents();

    DebugOverlay createDebugOverlay();

    uint32_t getWidth() const { return m_width; }
    uint32_t getHeight() const { return m_height; }

  private:
    uint32_t m_width, m_height;
    std::string title;

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> window;
};
