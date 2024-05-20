#version 330 core
out vec4 fragColor;

in vec4 worldPosition;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;



void main() {
    vec3 viewDir = normalize(worldPosition.xyz - cameraPosition);

    fragColor = vec4(1,0,0,1);
}
