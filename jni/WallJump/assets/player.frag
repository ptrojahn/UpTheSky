precision mediump float;

uniform vec3 color0;
uniform vec3 color1;
uniform vec3 color2;
uniform sampler2D atlas;
uniform int atlasIndex;

varying vec2 uvPos;

void main(){
	float pixel = texture2D(atlas, vec2((128./2048. + 8./2048.) * float(atlasIndex)  + uvPos.x * 128./2048., uvPos.y)).r;
	gl_FragColor = vec4(step(pixel, 0.25) * color0 + step(0.25, pixel) * step(pixel, .75) * color1 + step(0.75, pixel) * color2, 1.);
}