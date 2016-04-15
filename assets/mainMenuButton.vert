precision mediump float;

attribute vec2 position;
attribute vec2 uv;

uniform mat4 LE_matrix;

varying vec2 uvPos;

void main(){
	gl_Position = LE_matrix * vec4(position, 0, 1);
	uvPos = uv;
}