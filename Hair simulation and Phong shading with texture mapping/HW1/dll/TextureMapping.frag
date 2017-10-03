#version 150 compatibility

uniform sampler2D colorTexture;
in  vec4 final;
void main(){
    gl_FragColor = texture(colorTexture, gl_TexCoord[0].xy);
}
