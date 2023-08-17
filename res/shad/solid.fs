#version 400

in vec3 _pos;

vec3 sun = vec3(1.0, 0.0, -1.0);

const vec3 col = vec3(50, 50, 50);

void main() {
	vec3 normFace = normalize(cross(dFdx(_pos), dFdy(_pos)));

	float diff = max(dot(normFace, normalize(sun)), 0.0) * 0.2;

	gl_FragColor = vec4((1.0 - diff) * (col / 255.0), 1.0);
}
