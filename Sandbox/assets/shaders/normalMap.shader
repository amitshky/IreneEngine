#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vsOut;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

void main()
{
	vsOut.FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vsOut.TexCoords = a_TexCoords;
	vsOut.Normal = a_Normal;

	vec3 T   = normalize(mat3(u_Model) * a_Tangent);
	vec3 B   = normalize(mat3(u_Model) * a_Bitangent);
	vec3 N   = normalize(mat3(u_Model) * a_Normal);
	mat3 TBN = transpose(mat3(T, B, N));
	
	vsOut.TangentLightPos = TBN * u_LightPos;
	vsOut.TangentViewPos  = TBN * u_ViewPos;
	vsOut.TangentFragPos  = TBN * vsOut.FragPos;

	gl_Position = u_ViewProjection * vec4(vsOut.FragPos, 1.0f);
}

#shader fragment
#version 450 core

struct Materials
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	sampler2D height;
};

out vec4 FragColor;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fsIn;

uniform Materials u_Material;
uniform float u_HeightScale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	// steep parallax mapping
	// number of depth layers
	const float minLayers = 8.0;
	const float maxLayers = 32.0;
	float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));
	// calculate the size of each layer
	float layerDepth = 1.0 / numLayers;
	// depth of current layer
	float currentLayerDepth = 0.0;
	// the amount to shift the texture coordinates per layer (from vector P)
	vec2 P = viewDir.xy * u_HeightScale;
	vec2 deltaTexCoords = P / numLayers;

	// get initial values
	vec2  currentTexCoords = texCoords;
	float currentDepthMapValue = texture(u_Material.height, currentTexCoords).r;

	while (currentLayerDepth < currentDepthMapValue)
	{
		// shift texture coordinates along direction of P
		currentTexCoords -= deltaTexCoords;
		// get depthmap value at current texture coordinates
		currentDepthMapValue = texture(u_Material.height, currentTexCoords).r;
		// get depth of next layer
		currentLayerDepth += layerDepth;
	}

	// parallax occlusion mapping
	// get texture coordinates before collision (reverse operations)
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	// get depth after and before collision for linear interpolation
	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(u_Material.height, prevTexCoords).r - currentLayerDepth + layerDepth;

	// interpolation of texture coordinates
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}

void main()
{
	// offset texture coordinates with Parallax mapping
	vec3 viewDir   = normalize(fsIn.TangentViewPos - fsIn.TangentFragPos);
	vec2 texCoords = ParallaxMapping(fsIn.TexCoords, viewDir);
	if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;

	vec3 diffCol = texture(u_Material.diffuse,  texCoords).rgb;
	vec3 speCol  = texture(u_Material.specular, texCoords).rgb;
	vec3 normal  = texture(u_Material.normal,   texCoords).rgb;
	normal = normalize(normal * 2.0f - 1.0f);

	// ambient
	vec3 ambient = 0.1f * diffCol;
	// diffuse
	vec3 lightDir = normalize(fsIn.TangentLightPos - fsIn.TangentFragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * diffCol;
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
	vec3 specular = vec3(0.2f) * spec * speCol;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}
