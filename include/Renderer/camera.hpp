#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float speed;
    float sensitivity;
    float fov;

    Camera();
    void update(float dt);
    glm::mat4 getViewMatrix();

  private:
    float yaw   = -90.0f;
    float pitch = 0.0f;
};
