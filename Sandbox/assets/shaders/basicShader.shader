#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 fColor;

uniform vec2 offsets[100];

void main()
{
	vec2 offset = offsets[gl_InstanceID];
	gl_Position = vec4(a_Position + offset, 0.0, 1.0);
	fColor = a_Color;
}


#shader fragment
#version 450 core

out vec4 Color;

in vec3 fColor;

void main()
{
	Color = vec4(fColor, 1.0f);
}
