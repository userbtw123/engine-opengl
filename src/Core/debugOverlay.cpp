#include "Renderer/renderer.hpp"
#include "Renderer/scene.hpp"
#include "Core/debugOverlay.hpp"
#include "Renderer/camera.hpp"
#include "imgui.h"

DebugOverlay::DebugOverlay(GLFWwindow* window) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

DebugOverlay::~DebugOverlay() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DebugOverlay::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugOverlay::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugOverlay::drawMenu(Scene& scene) {
    ImGui::Begin("Welcome");
    ImGui::Text("Create or load a scene");
    ImGui::Button("Create a scene");
    ImGui::End();
}

void DebugOverlay::drawDebug(Camera& camera, Scene& scene, Renderer& renderer) {
    static bool polygonModeFill = true;
    ImGui::Begin("Debug");
    ImGui::Text("fps: %f", ImGui::GetIO().Framerate);

    float fov = camera.getFov();
    if (ImGui::SliderFloat("fov", &fov, 0, 180, "%.2f")) {
        camera.setFov(fov);
    }
    float speed = camera.getSpeed();
    if (ImGui::SliderFloat("camera speed", &speed, 1, 20, "%.2f")) {
        camera.setSpeed(speed);
    }
    float sensitivity = camera.getSensitivity();
    if (ImGui::SliderFloat("camera sensitivity", &sensitivity, 5, 50, "%.2f")) {
        camera.setSensitivity(sensitivity);
    }
    glm::vec3 pos = camera.getPos();
    if (ImGui::SliderFloat3("camera xyz", &pos[0], -50, 50, "%.2f")) {
        camera.setPos(pos);
    }
    (ImGui::ColorEdit3("background color", &renderer.background_color[0]));
    if (ImGui::Checkbox("Fill mode", &polygonModeFill)) {
        if (polygonModeFill)
            renderer.setPolygonMode(GL_FILL);
        else
            renderer.setPolygonMode(GL_LINE);
    }

    ImGui::Separator();
    if (ImGui::Begin("Objects")) {
        for (auto& obj : scene.getObjects()) {
            if (ImGui::TreeNode(obj->name.c_str())) {
                ImGui::DragFloat3("Pos", &obj->transform.position.x, 0.1f);
                ImGui::DragFloat3("Rot", &obj->transform.rotation.x, 1.0f);
                ImGui::DragFloat3("Scale", &obj->transform.scale.x, 1.0f);
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
    ImGui::End();
}
