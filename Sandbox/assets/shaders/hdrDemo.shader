#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out VS_OUT 
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vsOut;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform bool u_InverseNormals;

void main()
{
	vsOut.FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vsOut.TexCoords = a_TexCoords;
	
	vec3 n = u_InverseNormals ? -a_Normal : a_Normal;

	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	vsOut.Normal = normalize(normalMatrix * n);
	
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}

#shader fragment
#version 450 core

out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fsIn;

struct Light
{
	vec3 Position;
	vec3 Color;
};

uniform Light u_Lights[4];
uniform sampler2D u_DiffuseTex;

void main()
{
	vec3 color = texture(u_DiffuseTex, fsIn.TexCoords).rgb;
	vec3 normal = normalize(fsIn.Normal);

	// ambient
	vec3 ambient = 0.0f * color;
	// lighting
	vec3 lighting = vec3(0.0f);
	for (int i = 0; i < 4; i++)
	{
		// diffuse
		vec3 lightDir = normalize(u_Lights[i].Position - fsIn.FragPos);
		float diff = max(dot(lightDir, normal), 0.0f);
		vec3 diffuse = u_Lights[i].Color * diff * color;
		vec3 result = diffuse;
		// attenuation
		float distance = length(fsIn.FragPos - u_Lights[i].Position);
		result *= 1.0f / (distance * distance);
		lighting += result;
	}
	FragColor = vec4(ambient + lighting, 1.0f);
}
