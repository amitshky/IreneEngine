#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	Normal = mat3(transpose(inverse(u_Model))) * a_Normal; // the inverse part is very taxing on performance // it is used for non uniform scaling
	TexCoords = a_TexCoords;

	gl_Position = u_ViewProjection * vec4(FragPos, 1.0f);
}

#shader fragment
#version 450 core

struct Materials {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NUM_POINT_LIGHTS 1

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 u_ViewPos;
uniform Materials u_Material;

uniform DirLight u_DirLight;
uniform PointLight u_PointLight[NUM_POINT_LIGHTS];
uniform SpotLight u_SpotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal,  vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 FragPos, vec3 viewDir);

out vec4 Color;

void main()
{
	// Properties
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(u_ViewPos - FragPos);

	// Directional Lighting
	//vec3 result = CalcDirLight(u_DirLight, normal, viewDir);
	// Point Lights
	vec3 result;
	for (int i = 0; i < NUM_POINT_LIGHTS; i++)
		result += CalcPointLight(u_PointLight[i], normal, FragPos, viewDir);
	// Spot Light
	//vec3 result = CalcSpotLight(u_SpotLight, normal, FragPos, viewDir);
	Color = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), u_Material.shininess);

	vec3 ambient = light.ambient * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(u_Material.specular, TexCoords).rgb;
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), u_Material.shininess);

	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(u_Material.specular, TexCoords).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0f);
	// specular shading
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), u_Material.shininess);

	float theta = dot(lightDir, normalize(-light.direction));	// for spot light
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);	// clamps from 0 - 1
	
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(u_Material.specular, TexCoords).rgb;
	
	ambient *= attenuation;
	diffuse *= intensity * attenuation;
	specular *= intensity * attenuation;

	return (ambient + diffuse + specular);
}
