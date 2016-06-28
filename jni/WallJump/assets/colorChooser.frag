precision mediump float;

uniform float offset;
uniform float alpha;
uniform sampler2D colors;

varying vec2 uvPos;

void main(){
	float xPos = uvPos.x*18. - offset*2. - smoothstep(1./18.*8., 1./18.*10., uvPos.x);
	vec3 color = texture2D(colors, vec2(floor(xPos - 8.)/32., 0.)).bgr;
	gl_FragColor = vec4(color, alpha * step(8. + 0., xPos) * step(xPos, 8. + 32.));
}