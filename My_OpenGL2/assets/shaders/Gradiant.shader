#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0f);
}


#shader fragment
#version 330 core

out vec4 Color;
in vec4 v_Color;

void main()
{
	Color = v_Color;
}
