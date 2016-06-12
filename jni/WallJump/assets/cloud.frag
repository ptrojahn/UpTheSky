precision mediump float;

uniform int index;
uniform sampler2D texture;

varying vec2 uvPos;

void main(){
	vec2 position =  vec2(uvPos.x, (float(index) + uvPos.y) * (8. / 35.) + float(index) * (1. / 35.));
	gl_FragColor = vec4(1., 1., 1., texture2D(texture, position).r  * 0.3);
}