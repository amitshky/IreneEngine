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

uniform vec3 u_LightColor;

void main()
{
	FragColor = vec4(u_LightColor, 1.0f);
	// check if result is higher than some threshold, if so, output as bloom threshold color
	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722)); // comparing with greyscale for brightness threshold
	if (brightness > 1.0f)
		BrightnessColor = FragColor;
	else
		BrightnessColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
