#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vUV;
layout(location = 3) in vec3 vNormal;
layout(location = 4) in vec3 vTan;
layout(location = 5) in vec3 vBitan;

out vec3 color;
out vec2 uv;
out mat3 tbn;
out vec4 worldPosition;

uniform mat4 world, view, projection;

void main() {
	gl_Position = projection * view * world * vec4(vPos, 1.0);
	color = vColor;
	uv = vUV;
	
	vec3 t = normalize(mat3(world) * vTan);
	vec3 b = normalize(mat3(world) * vBitan);
	vec3 n = normalize(mat3(world) * vNormal);

	tbn = mat3(t, b, n);	

	worldPosition = world * vec4(vPos, 1.0);
}
