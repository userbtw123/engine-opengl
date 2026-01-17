#include "Renderer/camera.hpp"
#include "Core/input.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
    : pos(0, 0, 10), front(0, 0, -1), up(0, 1, 0), speed(5), fov(45.0f), sensitivity(5) {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}

void Camera::update(float dt) {
    right = glm::normalize(glm::cross(front, up));

    if (Input::isKeyPressed(GLFW_KEY_W)) {
        pos += front * speed * dt;
    }
    if (Input::isKeyPressed(GLFW_KEY_S)) {
        pos -= front * speed * dt;
    }
    if (Input::isKeyPressed(GLFW_KEY_A)) {
        pos -= right * speed * dt;
    }
    if (Input::isKeyPressed(GLFW_KEY_D)) {
        pos += right * speed * dt;
    }
    yaw += Input::offsetX * sensitivity * dt;
    pitch -= Input::offsetY * sensitivity * dt;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 f;
    f.x            = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y            = sin(glm::radians(pitch));
    f.z            = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front          = glm::normalize(f);
    Input::offsetX = 0.0f;
    Input::offsetY = 0.0f;
}
