#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Scene;
class Camera;
class Renderer;

class DebugOverlay {
  public:
    DebugOverlay(GLFWwindow* window);
    ~DebugOverlay();

    void begin();
    void drawDebug(Camera& camera, Scene& scene, Renderer& renderer);
    void drawMenu(Scene& scene);
    void end();
};
