precision mediump float;

varying vec2 uvPos;

void main(){
	gl_FragColor = vec4(0.31765, 0, 1, 1. * smoothstep(0.5, 0.48, distance(vec2(0.5, 0.5), uvPos)));
}