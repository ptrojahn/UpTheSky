precision mediump float;

uniform float time;

varying vec2 uvPos;

void main(){
	gl_FragColor = vec4(1., time, 0., smoothstep(0.5, 0.496, sqrt(pow(0.5 - uvPos.x, 2.) + pow(0.5 - uvPos.y, 2.))));
}