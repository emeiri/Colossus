uniform float gSpecExp;
uniform float gNumLights;

varying vec3 NormalV;
varying vec3 PosV;

vec4 CalcDirectionalLight(int Index, vec3 Normal)
{
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	VertexToLightV = normalize(VertexToLightV);

	vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));

	float SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gSpecExp);
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));

	vec4 ret = gl_Color * (gl_LightSource[Index].ambient + gl_LightSource[Index].diffuse * DiffuseFactor) + 
		   gl_LightSource[Index].specular * SpecularFactor;

	return ret;
}

vec4 CalcPointLight(int Index, vec3 Normal)
{
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	float Distance = length(VertexToLightV);
	VertexToLightV = normalize(VertexToLightV);

//	vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));
	vec3 HalfVectorV = normalize(VertexToLightV + vec3(0.0, 0.0, 1.0));

	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));
	float SpecularFactor;

	if (DiffuseFactor > 0.0)
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gSpecExp);
	else
		SpecularFactor = 0.0;
		
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation + 
			           gl_LightSource[Index].linearAttenuation * Distance + 
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);

	vec4 ret = gl_Color * (gl_LightSource[Index].ambient + gl_LightSource[Index].diffuse * DiffuseFactor) * Attenuation + 
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;

	return ret;
}

vec4 CalcSpotLight(int Index, vec3 Normal)
{
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	float Distance = length(VertexToLightV);
	VertexToLightV = normalize(VertexToLightV);

	//vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));
	vec3 HalfVectorV = normalize(VertexToLightV + vec3(0.0, 0.0, 1.0));

	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));
	float SpecularFactor;

	if (DiffuseFactor > 0.0)
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gSpecExp);
	else
		SpecularFactor = 0.0;
		
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation + 
			           gl_LightSource[Index].linearAttenuation * Distance + 
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);

	float SpotFactor = dot(-VertexToLightV, gl_LightSource[Index].spotDirection);
	float SpotAttenuation = 0.0;

	if (SpotFactor < gl_LightSource[Index].spotCutoff)
		SpotAttenuation = 0.0;
	else
		SpotAttenuation = pow(SpotFactor, gl_LightSource[Index].spotExponent);

	Attenuation *= SpotAttenuation;

	vec4 ret = gl_Color * (gl_LightSource[Index].ambient + gl_LightSource[Index].diffuse * DiffuseFactor) * Attenuation + 
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;

	return ret;
}

vec4 CalcLight(int Index, vec3 Normal)
{
	if (gl_LightSource[Index].position.w == 0.0)
		return CalcDirectionalLight(Index, Normal);
	else if (gl_LightSource[Index].spotCutoff == 180.0)
		return CalcPointLight(Index, Normal);
	else
		return CalcSpotLight(Index, Normal);
}

void main()
{	
	vec3 Normal = normalize(NormalV);

	gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);

	for (int i = 0 ; i < gNumLights ; i++)
	{
		gl_FragColor += CalcLight(i, Normal);
	}
}
