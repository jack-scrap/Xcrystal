#version 400

in vec3 _pos;

const float pad = 0.16;
const float sz = 2.0;

const float stride = sz + (pad * 2);

vec3[2] grey = vec3[2](
	vec3(30, 30, 30),
	vec3(100, 100, 100)
);

void main() {
	gl_FragColor = vec4(grey[int(mod(_pos.x, stride * 2) > stride ^^ mod(_pos.z, stride * 2) > stride)] / 225.0, 1.0);
}
