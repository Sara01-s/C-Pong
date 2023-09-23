#version 450 core

out vec4 o_FragColor;

in vec2 v_TexCoords;
in vec4 v_Color;

float make_circle(vec2 uv, float radius, float blur) {
    uv -= 0.5;
    float across_circle = 1.0 - length(uv) / radius;
    float circle_mask = smoothstep(0.0, max(0.01, blur), across_circle);
    return circle_mask;
}

void main() {
    vec3 circle_color = vec3(make_circle(v_TexCoords, 0.5, 0.0));
    o_FragColor = vec4(circle_color, circle_color.x) * v_Color;
}
