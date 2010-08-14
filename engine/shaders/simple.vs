uniform bool gIsFogEnabled;

const float e = 2.71828;

// vectors required by the fragment shader
varying vec3 VertexToLightV;
varying vec3 NormalV;
varying vec3 HalfVectorV;

varying float FogFactor;


void main()
{
	gl_Position = ftransform();
	gl_FrontColor = gl_Color;

	NormalV = normalize(gl_NormalMatrix * gl_Normal);
	vec4 PosV = gl_ModelViewMatrix * gl_Vertex;
	VertexToLightV = (gl_LightSource[0].position - PosV).xyz;
	HalfVectorV = VertexToLightV + vec3(0.0, 0.0, 1.0f);

	// fog
	if (gIsFogEnabled) {		
		FogFactor = pow(0.2 * length(PosV), 2.0);
		FogFactor = clamp(pow(e, -FogFactor), 0.0, 1.0);
	}
}
