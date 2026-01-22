#include "GLFW/glfw3.h"
#include "core/window.hpp"
#include <GL/gl.h>
#include <iostream>

int main() {
    auto res_window = Window::create("Hello!", 1280, 720);

    if (!res_window) {
        std::cerr << "Error: " << res_window.error();
        glfwTerminate();
        return -1;
    }

    auto& window = res_window.value();

    while (window.is_open()) {
        window.poll_events();
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        window.swap_buffers();
    }
}
