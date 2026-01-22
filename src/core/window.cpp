#include <expected>
#include <glad/glad.h>
#include "core/window.hpp"
#include <GLFW/glfw3.h>

std::expected<Window, std::string> Window::create(std::string_view title, int width, int height) {
    static bool glfwInitalized = false;
    // initalize glfw
    if (!glfwInitalized) {
        if (!glfwInit())
            return std::unexpected<std::string>{"Failed to initalize GLFW"};
        glfwInitalized = true;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create a window
    GLFWwindow* raw_handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!raw_handle)
        return std::unexpected<std::string>{"Failed to create GLFW window"};

    glfwMakeContextCurrent(raw_handle);

    static bool gladInitalized = false;
    // initalize glad
    if (!gladInitalized) {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            glfwDestroyWindow(raw_handle);
            return std::unexpected<std::string>{"Failed to initalize GLAD"};
        }
        gladInitalized = true;
    }

    return Window(raw_handle, width, height);
}

Window::Window(GLFWwindow* window, int w, int h) {
    m_handle.reset(window);

    m_width  = w;
    m_height = h;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

bool Window::is_open() const {
    return m_handle.get() && !glfwWindowShouldClose(m_handle.get());
}

void Window::poll_events() {
    glfwPollEvents();
}

void Window::swap_buffers() {
    glfwSwapBuffers(m_handle.get());
}
