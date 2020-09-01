#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec2 TexCoords;

out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} vs_out;

//uniform mat4 u_Projection;
//uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat4 u_LightSpaceMatrix;
uniform mat4 u_ViewProjection;


void main()
{
	vs_out.FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vs_out.Normal = transpose(inverse(mat3(u_Model))) * a_Normal;
	vs_out.TexCoords = a_TexCoords;
	vs_out.FragPosLightSpace = u_LightSpaceMatrix * vec4(vs_out.FragPos, 1.0f);
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}


#shader fragment
#version 450 core

out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D u_DiffuseTex;
uniform sampler2D u_ShadowMap;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

float ShadowCalculation(vec4 fragPosLightSpace, float dotLightNormal)
{
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0, 1] range
	projCoords = projCoords * 0.5 + 0.5;
	if (projCoords.z > 1.0f)
		projCoords.z = 1.0f;
	// get closest depth value form light's perspective (using [0, 1] range fragPosLight as coords)
	float closestDepth = texture(u_ShadowMap, projCoords.xy).r;
	// get depth of current fragment form light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow

	float bias = max(0.05 * (1.0 - dotLightNormal), 0.005);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(u_ShadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(u_ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	// keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

void main()
{
	vec3 color = texture(u_DiffuseTex, fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(0.3f);
	// ambient
	vec3 ambient = 0.3f * color;
	// diffuse
	vec3 lightDir = normalize(u_LightPos - fs_in.FragPos);
	float dotLightNormal = dot(lightDir, normal);
	float diff = max(dotLightNormal, 0.0f);
	vec3 diffuse = diff * lightColor;
	// specular
	vec3 viewDir = normalize(u_ViewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0f;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
	vec3 specular = spec * lightColor;
	// calculate shadow
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace, dotLightNormal);
	vec3 lighting = (ambient + (1.0f - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting, 1.0f);
}

