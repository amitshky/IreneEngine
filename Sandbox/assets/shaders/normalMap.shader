#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

out VS_OUT{
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vsOut;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main()
{
	vec3 FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vsOut.TexCoords = a_TexCoords;

	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	vec3 T = normalize(normalMatrix * a_Tangent);
	vec3 N = normalize(normalMatrix * a_Normal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));
	vsOut.TangentLightPos = TBN * u_LightPos;
	vsOut.TangentViewPos = TBN * u_ViewPos;
	vsOut.TangentFragPos = TBN * FragPos;

	gl_Position = u_ViewProjection * vec4(FragPos, 1.0f);
}

#shader fragment
#version 450 core

struct Materials
{
	sampler2D diffuse;
	sampler2D normal;
};

out vec4 FragColor;

in VS_OUT{
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fsIn;

uniform Materials u_Material;

void main()
{
	vec3 normal = texture(u_Material.normal, fsIn.TexCoords).rgb;
	normal = normalize(normal * 2.0f - 1.0f);

	vec3 color = texture(u_Material.diffuse, fsIn.TexCoords).rgb;

	// ambient
	vec3 ambient = 0.1f * color;
	// diffuse
	vec3 lightDir = normalize(fsIn.TangentLightPos - fsIn.TangentFragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * color;
	// specular
	vec3 viewDir = normalize(fsIn.TangentViewPos - fsIn.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
	vec3 specular = vec3(0.2f) * spec;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}
