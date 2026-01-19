#pragma once

#include <cstdint>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>

class Shader {
  public:
    Shader(const std::string& v_path, const std::string& f_path);
    ~Shader();
    int32_t fetchLocation(const std::string& name);

    void use();

    template <typename T> void setUniform(const std::string& name, const T& value) {
        int32_t location = fetchLocation(name);
        if (location == -1)
            return;
        if constexpr (std::is_same_v<T, float>) {
            glProgramUniform1f(program, location, value);
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, glm::value_ptr(value));
        }
    }

    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;

  private:
    uint32_t program;
    std::unordered_map<std::string, int32_t> locations;

    std::string readFile(const std::string& path);
};
