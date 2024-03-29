#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	Normal = mat3(transpose(inverse(u_Model))) * a_Normal; // the inverse part is very taxing on performance // it is used for non uniform scaling
	TexCoords = a_TexCoords;

	gl_Position = u_ViewProjection * vec4(FragPos, 1.0f);
}

#shader fragment
#version 450 core

out vec4 Color;

in vec2 TexCoords;

uniform sampler2D u_Texture;
uniform float u_Tile;
uniform vec4 u_Color;

void main()
{
	Color = texture(u_Texture, TexCoords * u_Tile) * u_Color;
}
