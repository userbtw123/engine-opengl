#include "Core/engine.hpp"
#include "Core/logger.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

int main() {
    try {
        Logger::init("log.txt");
        Engine engine("Hello!", 1280, 720);

        return engine.run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
