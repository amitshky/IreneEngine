#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords = a_TexCoords;
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0);
}

#shader fragment
#version 450 core

out vec4 Color;

in vec2 TexCoords;

uniform sampler2D u_ScreenTexture;

const float offset = 1.0 / 300.0;

void main()
{
	// post processing
	//vec3 col = 1.0f - texture(u_ScreenTexture, TexCoords).rgb;	// inversion
	//vec3 col = texture(u_ScreenTexture, TexCoords).rgb;
	//float average = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;	// greyscale
	//Color = vec4(average, average, average, 1.0f);
	
	// kernel
	//vec2 offsets[9] = vec2[](
	//	vec2(-offset, offset),	// top-left
	//	vec2(0.0f, offset),		// top-center
	//	vec2(offset, offset),	// top-right
	//	vec2(-offset, 0.0f),	// center-left
	//	vec2(0.0f, 0.0f),		// center-center
	//	vec2(offset, 0.0f),		// center-right
	//	vec2(-offset, -offset),	// bottom-left
	//	vec2(0.0f, -offset),	// bottom-center
	//	vec2(offset, -offset)	// bottom-right
	//);

	//float kernel[9] = float[](	// blur kernel
	//	1.0 / 16, 2.0 / 16, 1.0 / 16,
	//	2.0 / 16, 4.0 / 16, 2.0 / 16,
	//	1.0 / 16, 2.0 / 16, 1.0 / 16
	//);

	//vec3 sampleTex[9];
	//for (int i = 0; i < 9; i++)
	//{
	//	sampleTex[i] = vec3(texture(u_ScreenTexture, TexCoords.st + offsets[i]));
	//}
	//vec3 col = vec3(0.0);
	//for (int i = 0; i < 9; i++)
	//	col += sampleTex[i] * kernel[i];

	//Color = vec4(col, 1.0);

	vec3 col = texture(u_ScreenTexture, TexCoords).rgb;
	Color = vec4(col, 1.0f);
}
