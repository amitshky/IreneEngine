#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}

#shader fragment
#version 450 core

out vec4 FragColor;

uniform vec3 u_LightColor;

void main()
{
	FragColor = vec4(u_LightColor, 1.0f);
}
