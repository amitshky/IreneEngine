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

struct Light {
	vec3 position;
	vec3 direction;			// for directional light and spot light
	float cutOff;			// for spot light
	float outerCutOff;		// for smooth spot light

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

out vec4 Color;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 u_ViewPos;
uniform Materials u_Material;
uniform Light u_Light;

void main()
{
	// ambient
	vec3 ambient = u_Light.ambient * texture(u_Material.diffuse, TexCoords).rgb;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_Light.position - FragPos);	// since we only care about the direction
	float diff = max(dot(norm, lightDir), 0.0f);	//max function returns the highest of both its parameters to make sure the diffuse component (and thus the colors) never become negative
	vec3 diffuse = u_Light.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;		//resulting in a darker diffuse component the greater the angle is between both vectors
	
	// specular
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0f), u_Material.shininess);	// Blinn-Phong Lighting
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess); // the last parameter is the shininess value
	vec3 specular = u_Light.specular * spec * texture(u_Material.specular, TexCoords).rgb;
	
	// Intensity attenuation
	float distance = length(u_Light.position - FragPos);
	float attenuation = 1.0f / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	Color = vec4(result, 1.0f);
}
