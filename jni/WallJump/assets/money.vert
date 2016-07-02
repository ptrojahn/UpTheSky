attribute vec2 position;
attribute vec2 uv;

uniform mat4 LE_matrix;
uniform int money;
uniform int length;

varying vec2 uvPos;

void main(){
	gl_Position = LE_matrix * vec4(position*vec2(float(length) + 0.5, 1.), 0, 1);
	uvPos = uv*vec2(float(length) + 0.5, 1.);
}