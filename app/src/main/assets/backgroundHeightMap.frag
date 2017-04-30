precision mediump float;

uniform sampler2D texture;
uniform vec3 color;

varying vec2 uvPos;

void main(){
	float height = 0.5 - texture2D(texture, vec2(uvPos.x, 0.)).r * 0.5;
	gl_FragColor = vec4(color, smoothstep(height, height + 0.01, uvPos.y));
}