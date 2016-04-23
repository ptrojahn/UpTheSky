precision mediump float;

varying vec2 uvPos;

void main(){
	float edge = mod(floor(uvPos.x), 2.) != 0. ? fract(uvPos.x) : 1. - fract(uvPos.x);
	gl_FragColor = vec4(0.1, 0.1, 0.1, step(edge, uvPos.y));
}