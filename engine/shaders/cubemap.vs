// vectors required by the fragment shader
varying vec3 NormalV;
varying vec3 PosV;


void main()
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_Vertex;  

	NormalV = (gl_NormalMatrix * gl_Normal).xyz;
	PosV = (gl_ModelViewMatrix * gl_Vertex).xyz;
}
