precision mediump float;

uniform sampler2D texture;
uniform float alpha;

varying vec2 uvPos;

void main(){
	float textureAlpha = texture2D(texture, uvPos*1.5 - 0.25).r * step(1./6., uvPos.x) * step(uvPos.x, 5./6.) * step(1./6., uvPos.y) * step(uvPos.y, 5./6.);
	float dist = distance(vec2(0.5, 0.5), uvPos);
	gl_FragColor = vec4(vec3(1, 1, 1), alpha * (textureAlpha + smoothstep(0.5, 0.48, dist) * smoothstep(0.44, 0.46, dist)));
}