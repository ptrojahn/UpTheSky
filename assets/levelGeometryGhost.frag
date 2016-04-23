precision mediump float;

uniform bool isGhost;

void main(){
	gl_FragColor = vec4(0.1, 0.1, 0.1, 1. - float(isGhost)*0.5);
}