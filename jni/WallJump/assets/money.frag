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
	digit = mod(digit, 10.);

	float brightness = texture2D(digits, vec2(digit * (10. / 128.) + fract(uvPos.x)*(10. / 128.), uvPos.y)).r * (1. - step(float(length), uvPos.x));
	gl_FragColor = vec4(vec3(0., 0., 1.) * step(uvPos.x, float(length))
	                  + vec3(0., 1., 0.) * step(float(length), uvPos.x) * step(uvPos.x, float(length) + 1./4.)
	                  + vec3(1., 0., 0.) * step(float(length) + 1./4., uvPos.x), alpha) * (1. - brightness)
	             + vec4(vec3(1., 1., 1.), 1.) * brightness * alpha;
}