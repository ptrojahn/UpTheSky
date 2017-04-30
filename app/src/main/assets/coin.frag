precision mediump float;

uniform sampler2D digits;
uniform int digit;
uniform vec3 color;
uniform float animationState;

varying vec2 uvPos;

void main(){
	float innerIn = min(animationState, 0.4) * 0.75;
	float innerOut = (clamp(animationState, 0.6, 0.9) - 0.6);
	float outerOut = (max(animationState, 0.6) - 0.6) * 1.25;

	float minTextureU = (10. / 128.) * float(digit);
	float textureU = clamp((uvPos.x*3.2 - 1.2875) * (10. / 128.) + float(digit) * (10. / 128.), minTextureU, minTextureU + (10. / 128.));
	float textureAlpha = texture2D(digits, vec2(textureU, (uvPos.y*2. - 0.5))).r;
	float alpha = min(1., step(innerIn - innerOut, abs(uvPos.x - 0.5)) + step(innerIn - innerOut, abs(uvPos.y - 0.5)) + textureAlpha);
	float alphaOuter = 1. - min(1., step(0.5 - outerOut, abs(uvPos.x - 0.5)) + step(0.5 - outerOut, abs(uvPos.y - 0.5)));
	gl_FragColor = vec4(color, alpha * alphaOuter);
}