#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords   = a_TexCoords;
	gl_Position = vec4(a_Position, 0.0f, 1.0f);
}

#shader fragment
#version 450 core

out float FragColor;
in  vec2  TexCoords;

uniform sampler2D u_SSAOInput;

void main()
{
	vec2 texelSize = 1.0f / vec2(textureSize(u_SSAOInput, 0));
	float result = 0.0f;
	for (int x = -2; x < 2; x++)
	{
		for (int y = -2; y < 2; y++)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(u_SSAOInput, TexCoords + offset).r;
		}
	}
	FragColor = result / (4.0f * 4.0f);
}
