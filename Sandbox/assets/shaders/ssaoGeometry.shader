#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform bool u_InvertedNormals;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	vec4 viewPos = u_View * u_Model * vec4(a_Position, 1.0f); // we need position in viewspace
	FragPos = viewPos.xyz;
	
	Normal    = transpose(inverse(mat3(u_Model))) * (u_InvertedNormals ? -a_Normal : a_Normal);
	TexCoords = a_TexCoords;

	gl_Position = u_Projection * viewPos;
}

#shader fragment
#version 450 core

layout(location = 0) out vec3 g_Position;
layout(location = 1) out vec3 g_Normal;
layout(location = 2) out vec4 g_AlbedoSpec;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
	g_Position = FragPos;           // store the fragment position vector in the first gbuffer texture
	g_Normal = normalize(Normal);   // also store the per-fragment normals into the gbuffer
	g_AlbedoSpec.rgb = vec3(0.95f); // and the diffuse per-fragment color, ignore specular
}
