precision mediump float;

uniform sampler2D numbers;
uniform int length;
uniform int score;

varying vec2 uvPos;

void main(){
	float index = floor(uvPos.x);
	//Extract single character from score
	float digit = float(score);
	//Cut after the the digit
	digit = floor(digit / pow(10., float(length) - (index + 1.)));
	//Cut everything before the digit
	digit = fract(digit / 10.) * 10.;

	vec4 color = texture2D(numbers, vec2(digit * (10. / 128.) + fract(uvPos.x)*(10. / 128.), uvPos.y));
	gl_FragColor = vec4(color.rgb, 1. - color.r);
}