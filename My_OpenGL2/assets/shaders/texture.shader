#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
}


#shader fragment
#version 330 core

out vec4 Color;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_ContainerTexture;
//uniform sampler2D u_SmilieTexture;

void main()
{
	//Color = mix(texture(u_ContainerTexture, v_TexCoord), texture(u_SmilieTexture, v_TexCoord), 0.2f) * v_Color;
	Color = texture(u_ContainerTexture, v_TexCoord) * v_Color;
					// 0.2f = 80% of first texture and 20% of second texture
	//Color = vec4(v_TexCoord, 0.0f, 1.0f);
}
