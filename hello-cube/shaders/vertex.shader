#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vColor;

out vec3 color;

uniform mat4 world, view, projection;

void main() {
	gl_Position = projection * view * world * vec4(aPos.xyz, 1.0);
	color = vColor;
}
