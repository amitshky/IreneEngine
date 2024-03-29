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

uniform sampler2D u_HdrBuffer;
uniform bool u_HdrEnable;
uniform float u_Exposure;

void main()
{
	const float gamma = 2.2f;
	vec3 hdrColor = texture(u_HdrBuffer, TexCoords).rgb;
	if (u_HdrEnable)
	{
		// reinhard tone mapping algorithm
		//vec3 result = hdrColor / (hdrColor + vec3(1.0f));
		
		vec3 result = vec3(1.0f) - exp(-hdrColor * u_Exposure); // exposure
		// gamma correction
		result = pow(result, vec3(1.0f / gamma));
		FragColor = vec4(result, 1.0f);
	}
	else
	{
		vec3 result = pow(hdrColor, vec3(1.0f / gamma));
		FragColor = vec4(result, 1.0f);
	}
}
