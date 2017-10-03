#version 150 compatibility
uniform float length;
uniform int segment_num;
uniform vec3 gravity;
layout(triangles) in;
layout(line_strip, max_vertices=200) out;
in Vertex{
    vec3 normal;
}vertex[];
vec4 temp_pos;
vec4 norm_gra;
out float con_seg;
void main(){
	con_seg = 0;
    for(int i = 0; i < gl_in.length(); i++)
	{	
        //start point
		temp_pos = gl_in[i].gl_Position;
		norm_gra = normalize( vec4(vertex[i].normal + gravity,0.0f));
		for(int j = 0;j < segment_num;j++)
		{
			gl_Position = gl_ProjectionMatrix * temp_pos;
			EmitVertex();

			//end point 
			 gl_Position   = gl_ProjectionMatrix * (temp_pos + norm_gra * length );
			 temp_pos = temp_pos + norm_gra * length;
			 norm_gra = normalize( norm_gra + vec4(gravity,0.0f)); 
			 EmitVertex();
			 EndPrimitive();
			 con_seg = j;
		}
		
    }
}
