vec4 GetDirectionalLightIntensity(int Index, vec3 PosV, vec3 Normal)
{
	// should be simply the position
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	VertexToLightV = normalize(VertexToLightV);

	vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));

	float SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gl_LightSource[Index].spotExponent);
	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));

	vec4 ret = gl_LightSource[Index].ambient + 
		   gl_LightSource[Index].diffuse * DiffuseFactor + 
		   gl_LightSource[Index].specular * SpecularFactor;

	return ret;
}

vec4 GetPointLightIntensity(int Index, vec3 PosV, vec3 Normal)
{
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	float Distance = length(VertexToLightV);
	VertexToLightV = normalize(VertexToLightV);

	//vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));
	vec3 HalfVectorV = normalize(gl_LightSource[Index].halfVector.xyz);

	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));
	float SpecularFactor = 0.0;

	if (DiffuseFactor > 0.0) {
		SpecularFactor = max(0.0, dot(Normal, HalfVectorV)); 
		SpecularFactor = pow(SpecularFactor, gl_LightSource[Index].spotExponent);
	}
		
	float Attenuation = 1.0 / (gl_LightSource[Index].constantAttenuation + 
			           gl_LightSource[Index].linearAttenuation * Distance + 
				   gl_LightSource[Index].quadraticAttenuation * Distance * Distance);

	vec4 ret = gl_LightSource[Index].ambient + 
	           gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation + 
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;

	return ret;
}

vec4 GetSpotLightIntensity(int Index, vec3 PosV, vec3 Normal)
{
	vec3 VertexToLightV = gl_LightSource[Index].position.xyz - PosV;
	float Distance = length(VertexToLightV);
	VertexToLightV = normalize(VertexToLightV);

	//vec3 HalfVectorV = normalize(VertexToLightV - normalize(PosV));
	vec3 HalfVectorV = gl_LightSource[Index].halfVector.xyz;

	float DiffuseFactor = max(0.0, dot(Normal, VertexToLightV));
	float SpecularFactor;

	if (DiffuseFactor > 0.0)
		SpecularFactor = pow(max(0.0, dot(Normal, HalfVectorV)), gl_LightSource[Index].spotExponent);
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

	vec4 ret = gl_LightSource[Index].ambient + 
		   gl_LightSource[Index].diffuse * DiffuseFactor * Attenuation + 
		   gl_LightSource[Index].specular * SpecularFactor * Attenuation;

	return ret;
}

vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal)
{
	if (gl_LightSource[Index].position.w == 0.0)
		return GetDirectionalLightIntensity(Index, PosV, Normal);
	else if (gl_LightSource[Index].spotCutoff == 180.0)
		return GetPointLightIntensity(Index, PosV, Normal);
	else
		return GetSpotLightIntensity(Index, PosV, Normal);
}

