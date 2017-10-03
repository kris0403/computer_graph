#version 150 compatibility
uniform float length;
uniform int segment_num;
uniform vec3 gravity;
in float con_seg;
void main(){
	float r=0.0f;
	float g=0.0f;
	float b=0.0f;
	float a=0.0f;
	float mix_rgb = con_seg/segment_num;
	r = mix(0.0f,0.3f,mix_rgb);
	g = mix(0.0f,0.3f,mix_rgb);
	b = mix(0.0f,0.7f,mix_rgb);
	a = mix(1.0f,1.0f,mix_rgb);

    gl_FragColor = vec4(r, g, b, a);

}
