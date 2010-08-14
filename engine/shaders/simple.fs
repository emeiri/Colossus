uniform bool gIsFogEnabled;
uniform float gSpecExp;
uniform bool gIsBlackAndWhite;

varying vec3 VertexToLightV;
varying vec3 HalfVectorV;
varying vec3 NormalV;
varying float FogFactor;

void main()
{	
	if (gIsBlackAndWhite) {
		float Gray = dot(gl_Color.rgb, vec3(0.299, 0.587, 0.114));
		gl_FragColor = vec4(Gray, Gray, Gray, 1.0);
	}
	else if (gIsFogEnabled) {		
		float DiffuseFactor = max(0.0, dot(normalize(NormalV), normalize(VertexToLightV)));
		const vec4 FogColor = vec4(0.5, 0.5, 0.5, 1.0);
		gl_FragColor = mix(FogColor, gl_Color * vec4(DiffuseFactor), FogFactor);
	}
	else {
		float SpecularFactor = pow(max(0.0, dot(normalize(NormalV), normalize(HalfVectorV))), gSpecExp);
		float DiffuseFactor = max(0.0, dot(normalize(NormalV), normalize(VertexToLightV)));
		gl_FragColor = gl_Color * vec4(DiffuseFactor) + vec4(SpecularFactor);
	}
}
