attribute vec2 position;

uniform mat4 LE_matrix;

void main(){
	gl_Position = LE_matrix * vec4(position, 0, 1);
}