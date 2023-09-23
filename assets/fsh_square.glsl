#version 450 core

out vec4 o_FragColor;

in vec4 v_Color;
in vec2 v_TexCoords;

void main() {

    o_FragColor = v_Color;
}