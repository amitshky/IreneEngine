#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	TexCoords = a_TexCoords;
	FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	gl_Position = u_Projection * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core

out vec4 Color;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

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

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform Light u_Light;
uniform vec3 u_ViewPos;

void main()
{
	// ambient
	vec3 ambient = u_Light.ambient * texture(texture_diffuse1, TexCoords).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_Light.position - FragPos);	// since we only care about the direction
	float diff = max(dot(norm, lightDir), 0.0f);	//max function returns the highest of both its parameters to make sure the diffuse component (and thus the colors) never become negative
	vec3 diffuse = u_Light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;		//resulting in a darker diffuse component the greater the angle is between both vectors

	// specular
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0f), 32.0f);	// Blinn-Phong Lighting
	vec3 specular = u_Light.specular * spec * texture(texture_specular1, TexCoords).rgb;

	// spot light
	float theta = dot(lightDir, normalize(-u_Light.direction));	// for spot light
	float epsilon = u_Light.cutOff - u_Light.outerCutOff;
	float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0, 1.0);	// clamps from 0 - 1
	diffuse *= intensity;
	specular *= intensity;

	// Intensity attenuation
	float distance = length(u_Light.position - FragPos);
	float attenuation = 1.0f / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	Color = vec4(result, 1.0f);
}
