#version 450 core

uniform mat4 _MVP;

layout (location = 0) in vec2 Position;

void main() {
   gl_Position = _MVP * vec4(Position, 0.0, 1.0);
}