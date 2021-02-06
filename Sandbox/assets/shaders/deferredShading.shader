#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords = a_TexCoords;
	gl_Position = vec4(a_Position, 0.0f, 1.0f);
}

#shader fragment
#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

struct Light
{
	vec3 Position;
	vec3 Color;
	float Linear;
	float Quadratic;
};

const int NUM_LIGHTS = 32;
uniform Light u_Lights[NUM_LIGHTS];
uniform vec3 u_ViewPos;

// G-Buffer
uniform sampler2D u_PositionGBuff;
uniform sampler2D u_NormalGBuff;
uniform sampler2D u_AlbedoSpecGBuff;

void main()
{
	vec3 FragPos   = texture(u_PositionGBuff,   TexCoords).rgb;
	vec3 Normal    = texture(u_NormalGBuff,     TexCoords).rgb;
	vec3 Diffuse   = texture(u_AlbedoSpecGBuff, TexCoords).rgb;
	float Specular = texture(u_AlbedoSpecGBuff, TexCoords).a;

	vec3 lighting = Diffuse * 0.1f;  // hard-code ambient component
	vec3 viewDir  = normalize(u_ViewPos - FragPos);
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		// diffuse
		vec3 lightDir = normalize(u_Lights[i].Position - FragPos);
		vec3 diffuse  = max(dot(Normal, lightDir), 0.0f) * Diffuse * u_Lights[i].Color;
		// specular
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec      = pow(max(dot(Normal, halfwayDir), 0.0f), 16.0f);
		vec3 specular   = u_Lights[i].Color * spec * Specular;
		// attenuation
		float distance    = length(u_Lights[i].Position - FragPos);
		float attenuation = 1.0f / (1.0f + u_Lights[i].Linear * distance + u_Lights[i].Quadratic * distance * distance);
		
		diffuse  *= attenuation;
		specular *= attenuation;
		lighting += diffuse + specular;
	}
	FragColor = vec4(lighting, 1.0f);
}
