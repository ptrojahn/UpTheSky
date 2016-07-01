precision mediump float;

uniform float offset;
uniform float alpha;
uniform sampler2D atlas;
uniform sampler2D colors;
uniform int color0;
uniform int color1;
uniform int color2;

varying vec2 uvPos;

void main(){
	float localOffset = offset / 9. * (4.5/16.) + 1.75/16.;
	float atlasXPos = uvPos.x * (4.5/16.) - localOffset;
	float distance = abs(floor(atlasXPos*16.)/16.+ 0.5/16. + localOffset - (4.5/2.)/16.);

	vec3 grey = texture2D(atlas, vec2(atlasXPos, uvPos.y)).rgb;
	float pixel = texture2D(atlas, vec2(atlasXPos, uvPos.y)).r;
	vec3 color = texture2D(colors, vec2(float(color0)/32., 0.)).bgr * step(pixel, 0.25) 
	           + texture2D(colors, vec2(float(color2)/32., 0.)).bgr * step(0.25, pixel) * step(pixel, 0.75)
	           + texture2D(colors, vec2(float(color1)/32., 0.)).bgr * step(0.75, pixel);

	float fadeAnimation =  (2.*alpha - distance/((4.5/2.)/16.));
	gl_FragColor = vec4(mix(grey, color, smoothstep(1./16., 0., distance)), fadeAnimation * step(0., atlasXPos) * step(atlasXPos, 1.));
}