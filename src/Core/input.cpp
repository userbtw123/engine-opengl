#include "Core/input.hpp"

bool Input::keys[]        = {false};
bool Input::keysChanged[] = {false};
bool Input::mouseLocked   = false;

bool Input::firstMouse = true;
float Input::lastX     = 0.0f;
float Input::lastY     = 0.0f;
float Input::offsetX   = 0.0f;
float Input::offsetY   = 0.0f;

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < GLFW_KEY_LAST) {
        if (action == GLFW_PRESS) {
            keys[key]        = true;
            keysChanged[key] = true;
        } else if (action == GLFW_RELEASE) {
            keys[key]        = false;
            keysChanged[key] = true;
        }
    }
}

bool Input::isKeyPressed(int key) {
    return keys[key];
}

bool Input::isKeyJustPressed(int key) {
    bool result = keys[key] && keysChanged[key];
    if (result)
        keysChanged[key] = false;
    return result;
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!mouseLocked)
        return;

    if (firstMouse) {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }

    offsetX = xpos - lastX;
    offsetY = ypos - lastY;

    lastX = xpos;
    lastY = ypos;
}
