#include "Core/engine.hpp"
#include "Core/logger.hpp"
#include "Core/window.hpp"
#include "Renderer/renderer.hpp"

Engine::Engine(const std::string& title, int width, int height)
    : window(title, width, height), shader("assets/shaders/v.vert", "assets/shaders/f.frag"),
      renderer(), debugOverlay(window.createDebugOverlay()) {
    Logger::log(LogLevel::Info, "The Engine is initialized ({} {}x{})", title, width, height);
}

Engine::~Engine() {
    // TODO: delete all allocated huini
    Logger::log(LogLevel::Info, "The Engine destructor is called");
}

int Engine::run() {
    while (window.isOpen()) {
        renderer.clear(&renderer.background_color[0]);
        window.poolEvents();
        shader.use();
        float dt = window.calculate_dt();

        debugOverlay.begin();
        if (!current_scene) { // menu
            debugOverlay.drawMenu(*current_scene);
            debugOverlay.end();
            window.swapBuffers();
            continue;
        };
        // ---
        //     current_scene->m_camera.update(dt);
        //     renderer.clear(renderer.background_color[0], renderer.background_color[1],
        //                    renderer.background_color[2]); //  	(28,150,197)
        //
        //     glm::mat4 viewProjection =
        //         current_scene->m_camera.getProjMatrix() *
        //         current_scene->m_camera.getViewMatrix();
        //     shader.setUniform("viewProjection", viewProjection);
        //
        //     current_scene->render();
        //     // imgui
        //     debugOverlay.begin();
        //     debugOverlay.draw(current_scene->m_camera, *current_scene, renderer);
        //     debugOverlay.end();
        window.swapBuffers();
        // }

        // ---
    }
    return 1;
}
