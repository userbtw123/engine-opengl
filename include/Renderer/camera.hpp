#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    Camera();
    void update(float dt);

    void setFov(float new_fov);
    void setSpeed(float new_speed);
    void setSensitivity(float new_sens);
    void setPos(glm::vec3 new_pos);

    float getFov() { return fov; }
    float getSpeed() { return speed; }
    float getSensitivity() { return sensitivity; }
    glm::vec3 getPos() { return pos; }

    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();

  private:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float speed;
    float sensitivity;
    float fov;

    float yaw   = -90.0f;
    float pitch = 0.0f;
};
