#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords   = a_TexCoords;
	gl_Position = vec4(a_Position, 0.0f, 1.0f);
}

#shader fragment
#version 450 core

out vec4 FragColor;
in  vec2 TexCoords;

struct Light
{
	vec3 Position;
	vec3 Color;
	float Linear;
	float Quadratic;
};

uniform Light u_Light;

// G-Buffer
uniform sampler2D u_PositionGBuff;
uniform sampler2D u_NormalGBuff;
uniform sampler2D u_AlbedoSpecGBuff;
uniform sampler2D u_SSAO;

void main()
{
	vec3 FragPos       = texture(u_PositionGBuff,   TexCoords).rgb;
	vec3 Normal        = texture(u_NormalGBuff,     TexCoords).rgb;
	vec3 Diffuse       = texture(u_AlbedoSpecGBuff, TexCoords).rgb;
	float AmbOcclusion = texture(u_SSAO,            TexCoords).r;

	// lighting calculation
	vec3 ambient  = vec3(0.3f * Diffuse * AmbOcclusion);
	vec3 viewDir  = normalize(- FragPos); // viewPos = (0, 0, 0)
	// diffuse
	vec3 lightDir = normalize(u_Light.Position - FragPos);
	vec3 diffuse  = max(dot(Normal, lightDir), 0.0f) * Diffuse * u_Light.Color;
	// specular
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec      = pow(max(dot(Normal, halfwayDir), 0.0f), 8.0f);
	vec3 specular   = u_Light.Color * spec;
	// attenuation
	float distance    = length(u_Light.Position - FragPos);
	float attenuation = 1.0f / (1.0f + u_Light.Linear * distance + u_Light.Quadratic * distance * distance);
		
	diffuse  *= attenuation;
	specular *= attenuation;
	vec3 lighting = ambient + diffuse + specular;
	
	FragColor = vec4(lighting, 1.0f);
}
