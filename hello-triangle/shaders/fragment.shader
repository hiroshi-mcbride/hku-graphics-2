#version 330 core

out vec4 fragColor;
in vec2 fragCoord;


void main() {
    fragColor = vec4(fragCoord, 0.0, 1.0);
}
