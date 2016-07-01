precision mediump float;

uniform float alpha;
uniform int color0;
uniform sampler2D colors;

void main(){
	gl_FragColor = vec4(texture2D(colors, vec2(float(color0)/32., 0.)).bgr + vec3(0.25, 0.25, 0.25), alpha);
}