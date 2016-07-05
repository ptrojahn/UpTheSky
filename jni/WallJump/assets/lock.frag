precision mediump float;

uniform sampler2D texture;
uniform float alpha;
uniform float alphaUnlocked;

varying vec2 uvPos;

void main(){
	gl_FragColor = vec4(1., 1., 1., texture2D(texture, uvPos).r * alpha * alphaUnlocked);
}