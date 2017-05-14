precision mediump float;

uniform sampler2D texture;
uniform float alpha;

varying vec2 uvPos;

void main() {
    float textureAlpha = texture2D(texture, uvPos).r;
	gl_FragColor = vec4(1.0, 1.0, 1.0, alpha * textureAlpha);
}
