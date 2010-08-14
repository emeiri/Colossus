// vectors required by the fragment shader
varying vec3 NormalV;
varying vec3 PosV;


void main()
{
	gl_Position = ftransform();
	
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;  

	NormalV = (gl_NormalMatrix * gl_Normal).xyz;
	PosV = (gl_ModelViewMatrix * gl_Vertex).xyz;
}
