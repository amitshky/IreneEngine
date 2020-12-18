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
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
	vs_out.FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vs_out.Normal = transpose(inverse(mat3(u_Model))) * a_Normal;
	vs_out.TexCoords = a_TexCoords;
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
}


#shader fragment
#version 450 core

out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
}fs_in;

uniform sampler2D u_DiffuseTex;
uniform samplerCube u_DepthMap;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

uniform float u_FarPlane;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
	vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
	vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
	vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
	vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos)
{
	vec3 fragToLight = fragPos - u_LightPos;
	//float closestDepth = texture(u_DepthMap, fragToLight).r; // in the range [0, 1]
	//closestDepth *= u_FarPlane; // [0, farPlane]

	// pcf
	float currentDepth = length(fragToLight);
	float shadow = 0.0f;
	float bias = 0.15f;
	int samples = 20;

	float viewDistance = length(u_ViewPos - fragPos);
	float diskRadius = (1.0 + (viewDistance / u_FarPlane)) / 25.0f;
	for (int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(u_DepthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= u_FarPlane;   // undo mapping [0;1]
		if (currentDepth - bias > closestDepth)
			shadow += 1.0f;
	}
	shadow /= float(samples);

	//FragColor = vec4(vec3(closestDepth / u_FarPlane), 1.0f); // visualize depth cubemap
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
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * lightColor;
	// specular
	vec3 viewDir = normalize(u_ViewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0f;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
	vec3 specular = spec * lightColor;
	// calculate shadow
	float shadow = ShadowCalculation(fs_in.FragPos);
	vec3 lighting = (ambient + (1.0f - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting, 1.0f);
}

