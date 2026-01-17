#pragma once

#include <GLFW/glfw3.h>

class Input {
  public:
    static bool keys[GLFW_KEY_LAST];
    static bool keysChanged[GLFW_KEY_LAST];

    static bool mouseLocked;
    static bool firstMouse;
    static float lastX, lastY;
    static float offsetX, offsetY;

    static bool isKeyPressed(int key);
    static bool isKeyJustPressed(int key);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
};
