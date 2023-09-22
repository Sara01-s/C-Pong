#version 450 core

layout (location = 0) in vec2 a_Position;

uniform mat4 u_MVP;

void main() {
   gl_Position = u_MVP * vec4(a_Position, 0.0, 1.0);
}