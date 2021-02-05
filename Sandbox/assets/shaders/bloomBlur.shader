#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords = a_TexCoords;
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0f, 1.0f);
}

#shader fragment
#version 450 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Image;
uniform bool u_Horizontal;
uniform float u_Weights[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
	vec2 texOffset = 1.0f / textureSize(u_Image, 0); // get size of a single texel
	vec3 result = texture(u_Image, TexCoords).rgb * u_Weights[0];
	if (u_Horizontal) // for row
	{
		for (int i = 1; i < 5; i++) // multiplying adjacent texels on either side of the center texel
		{
			result += texture(u_Image, TexCoords + vec2(texOffset.x * i, 0.0f)).rgb * u_Weights[i];
			result += texture(u_Image, TexCoords - vec2(texOffset.x * i, 0.0f)).rgb * u_Weights[i];
		}
	}
	else // for col
	{
		for (int i = 1; i < 5; i++) // multiplying adjacent texels on either side of the center texel
		{
			result += texture(u_Image, TexCoords + vec2(0.0f, texOffset.y * i)).rgb * u_Weights[i];
			result += texture(u_Image, TexCoords - vec2(0.0f, texOffset.y * i)).rgb * u_Weights[i];
		}
	}
	FragColor = vec4(result, 1.0f);
}
