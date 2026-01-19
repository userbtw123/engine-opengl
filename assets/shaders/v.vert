#version 450 core

layout(location = 0) in vec3 apos;

uniform mat4 model;
uniform mat4 viewProjection;

void main() {
    gl_Position = viewProjection * model * vec4(apos, 1.0);
}
