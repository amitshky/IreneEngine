#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}

#shader fragment
#version 330 core

uniform vec3 u_Color;
out vec4 Color;

void main()
{
	Color = vec4(u_Color, 1.0f);
}
