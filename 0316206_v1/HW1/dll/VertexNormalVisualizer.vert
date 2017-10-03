#version 150 compatibility
uniform float length;
uniform int segment_num;
uniform vec3 gravity;
out Vertex{
    vec3 normal;
};

void main(){
    //both transfer from object space to eye space
    normal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewMatrix * gl_Vertex;
}
