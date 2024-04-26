#version 330 core

out vec4 fragColor;
in vec3 color;
in vec2 uv;
in vec4 worldPosition;
in mat3 tbn;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec3 lightPosition;



void main() {

    vec3 normal = texture(normalMap, uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = tbn * normal;

    vec3 lightDirection = normalize(worldPosition.xyz - lightPosition);
    float brightness = max(-dot(normal, lightDirection), 0.0);

    fragColor = vec4(color, 1.0f) * texture(diffuseMap, uv) * min(brightness + 0.1, 1.0);
    //fragColor = vec4(normal, 1.0);
}
