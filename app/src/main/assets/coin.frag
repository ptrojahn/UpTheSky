precision mediump float;

uniform sampler2D digits;
uniform int digit;
uniform vec3 color;
uniform float animationState;

varying vec2 uvPos;

void main(){
	float stage0 = min(animationState, 0.4) * 2.5;//Open the center of the cube
	float stage1 = clamp(animationState - 0.6, 0., 0.2) * 5.;//Close the center of the cube
	float stage2 = (max(animationState, 0.6) - 0.6) * 2.5;//Remove the cube

    //Digit
    const float digitSizeY = 0.6;
    const float digitSizeX = digitSizeY * (4./7.);
	float textureUMin = (10. / 128.) * float(digit);
	float textureU = clamp(((uvPos.x - (1. - digitSizeX) / 2.) / digitSizeX + float(digit)) * (10. / 128.), textureUMin, textureUMin + (10. / 128.));
	float textureV = (uvPos.y - (1. - digitSizeY) / 2.) / digitSizeY;
	float textureAlpha = texture2D(digits, vec2(textureU, textureV)).r;

    //Border
    const float borderWidth = 0.8;
    float distX = abs(uvPos.x - 0.5) * 2.;
    float distY = abs(uvPos.y - 0.5) * 2.;
    float stage01Border = min(stage0 * borderWidth, (1. - stage1) * borderWidth);
    float stage2Border = 1. - stage2;
    float stage01Alpha = step(stage01Border, distX) + step(stage01Border, distY);
    float stage2Alpha = 1. - min(1., step(stage2Border, distX) + step(stage2Border, distY));

	gl_FragColor = vec4(color, (stage01Alpha + textureAlpha) * stage2Alpha);
}