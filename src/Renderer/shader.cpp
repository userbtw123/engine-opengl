#include "Renderer/shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string& v_path, const std::string& f_path) {
    std::ifstream f_file(f_path);

    std::string v_code = readFile(v_path);
    std::string f_code = readFile(f_path);

    uint32_t vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vertex_shader) {
        throw std::runtime_error("Failed to create vertex shader");
    }
    if (!fragment_shader) {
        glDeleteShader(vertex_shader);
        throw std::runtime_error("Failed to create fragment shader");
    }

    const char* v_ptr = v_code.c_str();
    const char* f_ptr = f_code.c_str();

    glShaderSource(vertex_shader, 1, &v_ptr, nullptr);
    glShaderSource(fragment_shader, 1, &f_ptr, nullptr);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    int ok;
    char infolog[1024];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderInfoLog(vertex_shader, sizeof(infolog), nullptr, infolog);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        throw std::runtime_error("Failed to compile vertex shader: " + (std::string) infolog);
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderInfoLog(fragment_shader, sizeof(infolog), nullptr, infolog);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        throw std::runtime_error("Failed to compile fragment shader: " + (std::string) infolog);
    }

    program = glCreateProgram();
    if (!program) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        throw std::runtime_error("Failed to create program shader");
    }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &ok);

    if (!ok) {
        glGetProgramInfoLog(program, sizeof(infolog), nullptr, infolog);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);

        throw std::runtime_error("Failed to link program shader: " + (std::string) infolog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() {
    if (program) {
        glDeleteProgram(program);
    }
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open vertex file: " + path);
    }
    std::stringstream buff;

    buff << file.rdbuf();
    return buff.str();
}

void Shader::use() {
    glUseProgram(program);
}

int32_t Shader::fetchLocation(const std::string& name) {
    auto it = locations.find(name);
    if (it != locations.end()) {
        return it->second;
    }
    int32_t loc     = glGetUniformLocation(program, name.c_str());
    locations[name] = loc;
    return loc;
}
