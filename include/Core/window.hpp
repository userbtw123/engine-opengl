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

    float calculate_dt();

    DebugOverlay createDebugOverlay();

    static uint32_t getWidth() { return m_width; }
    static uint32_t getHeight() { return m_height; }

  private:
    static uint32_t m_width, m_height;
    std::string title;

    double lastFrame;

    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> window;

    static void framebufferSizeCallback(GLFWwindow* window, int w, int h);
};
