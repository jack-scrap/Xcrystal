#version 400

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 pos;

out vec3 _pos;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);

	_pos = pos;
}
