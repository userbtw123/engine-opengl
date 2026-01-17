#include "Renderer/game_object.hpp"
#include "Renderer/scene.hpp"
#include "Renderer/shader.hpp"
#include "Renderer/renderer.hpp"
#include "Core/window.hpp"
#include "Renderer/camera.hpp"
#include "Renderer/mesh.hpp"
#include "imgui.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <memory>
#include <string>

int main() {
    try {
        Window window("ENGINE??", 700, 400);
        auto shader = std::make_shared<Shader>("assets/shaders/v.vert", "assets/shaders/f.frag");
        Camera camera;
        Renderer renderer;
        auto debugOverlay = window.createDebugOverlay();

        // Scene & data
        Scene scene("First scene", shader);
        auto cube = Mesh::createCube();
        for (int i = 0; i < 10; i++) {
            GameObject obj("cube " + std::to_string(i), cube);
            scene.objects.push_back(obj);
        }

        // loop
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        double lastFrame = 0.0;
        while (window.isOpen()) {
            window.poolEvents();
            shader->use();

            double current_frame = glfwGetTime();
            float dt             = current_frame - lastFrame;
            lastFrame            = current_frame;
            camera.update(dt);
            renderer.clear(28.0 / 255, 150.0 / 255, 197.0 / 255); //  	(28,150,197)

            glm::mat4 model = glm::mat4(1.0f);
            model           = glm::translate(model, glm::vec3{0, 0, 0});
            model           = glm::rotate(model, (float) glfwGetTime(), glm::vec3{0, 1, 0});

            shader->setUniform("view", camera.getViewMatrix());
            shader->setUniform(
                "projection", glm::perspective(glm::radians(camera.fov),
                                               float(window.getWidth()) / float(window.getHeight()),
                                               0.1f, 10000.0f));

            scene.render();
            // imgui
            debugOverlay.begin();
            ImGui::Begin("Debug");
            ImGui::Text("fps: %f", ImGui::GetIO().Framerate);
            ImGui::Text("camera pos: xyz: %f %f %f", camera.pos[0], camera.pos[1], camera.pos[2]);
            ImGui::SliderFloat("fov", &camera.fov, 0, 180, "%.2f");
            ImGui::SliderFloat("camera speed", &camera.speed, 1, 20, "%.2f");
            ImGui::SliderFloat("camera sensitivity", &camera.sensitivity, 5, 50, "%.2f");
            ImGui::SliderFloat3("camera xyz", &camera.pos[0], -50, 50, "%.2f");

            if (ImGui::Begin("Hierarchy")) {
                for (auto& obj : scene.objects) {
                    if (ImGui::TreeNode(obj.name.c_str())) {
                        ImGui::DragFloat3("Pos", &obj.transform.position.x, 0.1f);
                        ImGui::DragFloat3("Rot", &obj.transform.rotation.x, 1.0f);
                        ImGui::DragFloat3("Scale", &obj.transform.scale.x, 1.0f);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::End();

            ImGui::End();
            debugOverlay.end();

            window.swapBuffers();
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
