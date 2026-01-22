#pragma once

#include <expected>
#include <memory>
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>

struct windowDeleter {
    void operator()(GLFWwindow* window) {
        if (window) {
            glfwDestroyWindow(window);
        }
    }
};

class Window {
  private:
    std::unique_ptr<GLFWwindow, windowDeleter> m_handle;
    int m_width;
    int m_height;

    void onResize(int w, int h) {
        m_width  = w;
        m_height = h;
        glViewport(0, 0, m_width, m_height);
    }

    static void framebuffer_size_callback(GLFWwindow* handle, int w, int h) {
        auto* obj = static_cast<Window*>(glfwGetWindowUserPointer(handle));
        if (obj) {
            obj->onResize(w, h);
        }
    }
    Window(GLFWwindow* window, int w, int h);

  public:
    static std::expected<Window, std::string> create(std::string_view title, int width, int height);

    bool is_open() const;
    void poll_events();
    void swap_buffers();
};
