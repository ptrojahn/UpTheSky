precision mediump float;

uniform sampler2D digits;
uniform int length;
uniform int score;
uniform float alpha;
uniform vec3 textColor;

varying vec2 uvPos;

void main(){
	float index = floor(uvPos.x);
	//Extract single digit from score
	float digit = float(score);
	digit = floor(digit / pow(10., float(length) - (index + 1.)));
	digit -= float(int(digit)/10*10);

	float brightness = texture2D(digits, vec2(digit * (10. / 128.) + fract(uvPos.x)*(10. / 128.), uvPos.y)).r;
	gl_FragColor = vec4(textColor.rgb, brightness * alpha);
}