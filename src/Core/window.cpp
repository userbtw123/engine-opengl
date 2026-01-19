#include <glad/glad.h>
#include "Core/window.hpp"
#include "Core/input.hpp"
#include "Core/logger.hpp"
#include "GLFW/glfw3.h"

#include <stdexcept>

uint32_t Window::m_width  = 1280;
uint32_t Window::m_height = 720;

Window::Window(const std::string& title, uint32_t width, uint32_t height) : title(title) {
    m_width  = width;
    m_height = height;
    if (!glfwInit()) {
        Logger::log(LogLevel::Critical, "Failed to initalize GLFW");
        throw std::runtime_error("Failed to initalize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.reset(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));
    if (!window) {
        Logger::log(LogLevel::Critical, "Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Logger::log(LogLevel::Critical, "Failed to create GLAD");
        throw std::runtime_error("Failed to initalize GLAD");
    }

    glfwSetFramebufferSizeCallback(window.get(), framebufferSizeCallback);
    glfwSetKeyCallback(window.get(), Input::keyCallback);
    glfwSetCursorPosCallback(window.get(), Input::mouseCallback);
    // glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Window::isOpen() {
    return window && !glfwWindowShouldClose(window.get());
}

void Window::poolEvents() {
    glfwPollEvents();
    if (Input::isKeyJustPressed(GLFW_KEY_ESCAPE)) {
        Input::mouseLocked = !Input::mouseLocked;
        if (Input::mouseLocked) {
            glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            Input::firstMouse = true;
        }
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(window.get());
}

DebugOverlay Window::createDebugOverlay() {
    return DebugOverlay(window.get());
}

float Window::calculate_dt() {
    double currentFrame = glfwGetTime();
    float dt            = currentFrame - lastFrame;
    lastFrame           = currentFrame;
    return dt;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
    m_width  = w;
    m_height = h;
}
