#version 330 core

out vec4 fragColor;
in vec3 color;
in vec2 uv;
in vec4 worldPosition;
in mat3 tbn;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 cameraPosition;



void main() {
    //normal
    vec3 normal = texture(normalMap, uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = tbn * normal;
    
    // ambient light
    float ambientStrength = 0.5;
    vec4 ambient = vec4(lightColor.rgb * ambientStrength, lightColor.a);

    // diffuse light
    vec3 lightDirection = normalize(worldPosition.xyz - lightPosition);


    //specular
    vec3 viewDir = normalize(worldPosition.xyz - cameraPosition);
    vec3 reflectionDir = normalize(reflect(lightDirection, normal));


    float brightness = max(-dot(normal, lightDirection), 0.0);
    float highlight = pow(max(-dot(reflectionDir, viewDir), 0.0), 8);

    vec4 result = vec4(color, 1.0f) * texture(diffuseMap, uv);
    result.rgb = result.rgb * min(brightness + ambientStrength, 1.0) + highlight;
    fragColor = result;
    //fragColor = vec4(normal, 1.0);
}
