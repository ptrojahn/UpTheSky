precision mediump float;

uniform sampler2D digits;
uniform int length;
uniform int money;
uniform float alpha;

varying vec2 uvPos;

void main(){
	float index = floor(uvPos.x);
	//Extract single digit
	float digit = float(money);
	digit = floor(digit / pow(10., float(length) - (index + 1.)));
	digit -= float(int(digit)/10*10);

	float brightness = texture2D(digits, vec2(digit * (10. / 128.) + fract(uvPos.x)*(10. / 128.), uvPos.y)).r * (1. - step(float(length), uvPos.x));
	gl_FragColor = vec4(vec3(1., 1., 1.), alpha * (brightness + step(float(length), uvPos.x) * step(0.34375, uvPos.y) * step(uvPos.y, 0.65625)));
}