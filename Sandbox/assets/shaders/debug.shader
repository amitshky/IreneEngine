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
in  vec2 TexCoords;

uniform sampler2D u_FboAttachment;
//uniform sampler2D u_PositionGBuff;
//uniform sampler2D u_NormalGBuff;
//uniform sampler2D u_AlbedoSpecGBuff;

void main()
{
	//vec3 FragPos   = texture(u_PositionGBuff,   TexCoords).rgb;
	//vec3 Normal    = texture(u_NormalGBuff,     TexCoords).rgb;
	//vec3 Diffuse   = texture(u_AlbedoSpecGBuff, TexCoords).rgb;
	//float Specular = texture(u_AlbedoSpecGBuff, TexCoords).a;

	//FragColor = vec4(Normal, 1.0f);

	float val = texture(u_FboAttachment, TexCoords).r;
	FragColor = vec4(val, val, val, 1.0f);
}

