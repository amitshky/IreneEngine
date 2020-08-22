#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

out vec3 TexCoords;

uniform mat4 u_ViewProjection;

void main()
{
	TexCoords = a_Position;
	vec4 pos = u_ViewProjection * vec4(a_Position, 1.0f);
	gl_Position = pos.xyww;
}


#shader fragment
#version 450 core

out vec4 Color;

in vec3 TexCoords;

uniform samplerCube u_Skybox;

void main()
{
	Color = texture(u_Skybox, TexCoords);
}
