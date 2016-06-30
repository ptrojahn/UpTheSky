precision mediump float;

uniform int color0;
uniform int color1;
uniform int color2;
uniform sampler2D atlas;
uniform sampler2D colors;
uniform int atlasIndex;
uniform vec2 uvOffset;

varying vec2 uvPos;

void main(){
	float pixel = texture2D(atlas, vec2(1./16. * float(atlasIndex)  + (uvPos.x / 2. + uvOffset.x) * 8./128., uvPos.y / 4. + uvOffset.y)).r;
	vec3 color = texture2D(colors, vec2(float(color0)/32., 0.)).bgr * step(pixel, 0.25) 
	           + texture2D(colors, vec2(float(color1)/32., 0.)).bgr * step(0.25, pixel) * step(pixel, 0.75)
	           + texture2D(colors, vec2(float(color2)/32., 0.)).bgr * step(0.75, pixel);
	gl_FragColor = vec4(color, 1.);
}