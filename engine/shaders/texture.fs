uniform int gNumLights;

varying vec3 NormalV;
varying vec3 PosV;

uniform sampler2D TextureSampler;

vec4 GetLightIntensity(int Index, vec3 PosV, vec3 Normal);

void main()
{
	vec4 Texel = texture2D(TextureSampler, gl_TexCoord[0].st);

	if (Texel.x <= 0.001) {
		gl_FragColor = vec4(0.4, 0.4, 0.4, 1.0);
	}
	else {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	
		for (int i = 0 ; i < gNumLights ; i++)
		{
			gl_FragColor += Texel * GetLightIntensity(i, PosV, normalize(NormalV));
		}	
	}
}
	
