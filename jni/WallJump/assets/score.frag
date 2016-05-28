precision mediump float;

uniform sampler2D numbers;
uniform int length;
uniform int score;
uniform float alpha;

varying vec2 uvPos;

void main(){
	float index = floor(uvPos.x);
	//Extract single digit from score
	float digit = float(score);
	digit = floor(digit / pow(10., float(length) - (index + 1.)));
	digit = mod(digit, 10.);

	vec4 color = texture2D(numbers, vec2(digit * (10. / 128.) + fract(uvPos.x)*(10. / 128.), uvPos.y));
	gl_FragColor = vec4(color.rgb, (1. - color.r) * alpha);
}