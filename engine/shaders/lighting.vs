// vectors required by the fragment shader
varying vec3 NormalV;
varying vec3 PosV;


void main()
{
	gl_Position = ftransform();
	gl_FrontColor = gl_Color;

	NormalV = (gl_NormalMatrix * gl_Normal).xyz;
	PosV = (gl_ModelViewMatrix * gl_Vertex).xyz;
}
