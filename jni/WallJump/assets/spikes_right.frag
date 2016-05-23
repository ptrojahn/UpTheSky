precision mediump float;

varying vec2 uvPos;

void main(){
	float edge = mod(floor(uvPos.y), 2.) != 0. ? 1. - fract(uvPos.y) : fract(uvPos.y);
	gl_FragColor = vec4(0.1, 0.1, 0.1, step(uvPos.x, edge));
}