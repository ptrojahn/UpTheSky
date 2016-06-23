precision mediump float;

uniform vec3 color0;
uniform vec3 color1;
uniform vec3 color2;
uniform sampler2D atlas;
uniform int atlasIndex;
uniform vec2 uvOffset;

varying vec2 uvPos;

void main(){
	float pixel = texture2D(atlas, vec2(1./16. * float(atlasIndex)  + (uvPos.x / 2. + uvOffset.x) * 8./128., uvPos.y / 4. + uvOffset.y)).r;
	gl_FragColor = vec4(step(pixel, 0.25) * color0 + step(0.25, pixel) * step(pixel, .75) * color1 + step(0.75, pixel) * color2, 1.);
}