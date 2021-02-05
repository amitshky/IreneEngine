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

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	vsOut.FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vsOut.TexCoords = a_TexCoords;
	vsOut.Normal = normalize(transpose(inverse(mat3(u_Model))) * a_Normal);

	gl_Position = u_ViewProjection * vec4(vsOut.FragPos, 1.0f);
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightnessColor;

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
uniform vec3 u_ViewPos;

void main()
{
	vec3 color  = texture(u_DiffuseTex, fsIn.TexCoords).rgb;
	vec3 normal = normalize(fsIn.Normal);
	// ambient
	vec3 ambient = 0.0f * color;
	// lighting
	vec3 lighting = vec3(0.0f);
	vec3 viewDir  = normalize(u_ViewPos - fsIn.FragPos);
	for (int i = 0; i < 4; i++)
	{
		// diffuse
		vec3 lightDir = normalize(u_Lights[i].Position - fsIn.FragPos);
		float diff  = max(dot(lightDir, normal), 0.0f);
		vec3 result = u_Lights[i].Color * diff * color;
		// attenuation
		float distance = length(fsIn.FragPos - u_Lights[i].Position);
		result *= 1.0f / (distance * distance);
		lighting += result;
	}
	vec3 result = ambient + lighting;
	// check if result is higher than some threshold, if so, output as bloom threshold color
	float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722)); // comparing with greyscale for brightness threshold
	if (brightness > 1.0f)
		BrightnessColor = vec4(result, 1.0f);
	else
		BrightnessColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	FragColor = vec4(result, 1.0f);
}
