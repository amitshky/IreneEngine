#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	TexCoords = a_TexCoords;
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment
#version 450 core

out vec4 Color;

in vec2 TexCoords;

uniform sampler2D u_Texture;

void main()
{
	Color = texture(u_Texture, TexCoords);
}
