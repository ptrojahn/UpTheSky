precision mediump float;

uniform sampler2D texture;
uniform float alpha;

varying vec2 uvPos;

void main(){
	float textureAlpha = texture2D(texture, uvPos*1.5 - 0.25).r * step(1./6., uvPos.x) * step(uvPos.x, 5./6.) * step(1./6., uvPos.y) * step(uvPos.y, 5./6.);
	float distX = abs(uvPos.x - 0.5);
	float distY = abs(uvPos.y - 0.5);
	gl_FragColor = vec4(vec3(1, 1, 1), alpha * (textureAlpha + step(0.46, distX) + step(0.46, distY)));
}