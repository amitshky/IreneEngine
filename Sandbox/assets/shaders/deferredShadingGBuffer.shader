#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	FragPos   = vec3(u_Model * vec4(a_Position, 1.0f));
	Normal    = transpose(inverse(mat3(u_Model))) * a_Normal;
	TexCoords = a_TexCoords;

	gl_Position = u_ViewProjection * vec4(FragPos, 1.0f);
}

#shader fragment
#version 450 core

layout(location = 0) out vec3 g_Position;
layout(location = 1) out vec3 g_Normal;
layout(location = 2) out vec4 g_AlbedoSpec;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D u_TextureDiffuse1;
uniform sampler2D u_TextureSpecular1;

void main()
{
	g_Position = FragPos;           // store the fragment position vector in the first gbuffer texture
	g_Normal   = normalize(Normal); // also store the per-fragment normals into the gbuffer
	g_AlbedoSpec.rgb = texture(u_TextureDiffuse1,  TexCoords).rgb; // and the diffuse per-fragment color
	g_AlbedoSpec.a   = texture(u_TextureSpecular1, TexCoords).r;  // store specular intensity in gAlbedoSpec's alpha component
}
