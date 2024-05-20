#version 330 core

out vec4 FragColor;
in vec2 FragCoord;


void main() {
    FragColor = vec4(FragCoord, 0.0, 1.0);
}
