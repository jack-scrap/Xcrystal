#version 400

in vec3 _pos;

const vec3 col = vec3(50 / 255.0, 50 / 255.0, 50 / 255.0);

void main() {
	gl_FragColor = vec4(col, 1.0);
}
