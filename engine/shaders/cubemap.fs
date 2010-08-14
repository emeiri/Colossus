uniform int gNumLights;

varying vec3 NormalV;
varying vec3 PosV;

uniform samplerCube CubeMap;

vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal);

void main()
{
	vec3 Normal = normalize(NormalV);
	vec3 ReflectionVector = reflect(PosV, Normal);	

	vec4 Texel = textureCube(CubeMap, ReflectionVector);

	gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	
	for (int i = 0 ; i < gNumLights ; i++)
	{
		gl_FragColor += Texel * GetLightIntensity(i, PosV, NormalV);
	}	

	//gl_FragColor = Texel;
}
	
