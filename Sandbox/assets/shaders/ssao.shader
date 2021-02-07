#shader vertex
#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords   = a_TexCoords;
	gl_Position = vec4(a_Position, 0.0f, 1.0f);
}

#shader fragment
#version 450 core

out float FragColor;
in  vec2  TexCoords;

uniform sampler2D u_PositionGBuff;
uniform sampler2D u_NormalGBuff;
uniform sampler2D u_TexNoise;

uniform vec3 samples[64];

// use them as uniforms later
int   kernelSize = 64;
float radius = 0.5f;
float bias = 0.025f;

// tile noise texture over screen
const vec2 noiseScale = vec2(800.0f / 4.0f, 600.0f / 4.0f);

uniform mat4 u_Projection;

void main()
{
	// get input for SSAO
	vec3 fragPos = texture(u_PositionGBuff, TexCoords).xyz;
	vec3 normal  = normalize(texture(u_NormalGBuff, TexCoords).rgb);
	vec3 randVec = normalize(texture(u_TexNoise, TexCoords * noiseScale).xyz);
	// create TBN change-of-bias matrix: from tangent-space to view-space
	vec3 tangent   = normalize(randVec - normal * dot(randVec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN       = mat3(tangent, bitangent, normal);
	
	// iterate over the sample kernel and calculate occlusion factor
	float occlusion = 0.0f;
	for (int i = 0; i < kernelSize; i++)
	{
		// get sample position
		vec3 samplePos = TBN * samples[i]; // from tangent to view-space
		samplePos = fragPos + samplePos * radius;

		// project sample position (to sample texture) (to get position on screen/texture)
		vec4 offset = vec4(samplePos, 1.0f);
		offset = u_Projection * offset; // from view to clip-space
		offset.xyz /= offset.w;         // perspective divide
		offset.xyz = offset.xyz * 0.5f + 0.5f; // transform to range 0.0 - 1.0

		// get sample depth
		float sampleDepth = texture(u_PositionGBuff, offset.xy).z; // get depth value of kernel sample

		// range check & accumulate
		// Whenever a fragment is tested for ambient occlusion that is aligned close to the edge of a surface, 
		// it will also consider depth values of surfaces far behind the test surface, so a range check is done
		float rangeCheck = smoothstep(0.0f, 1.0f, radius / abs(fragPos.z - sampleDepth)); // smoothly interpolates 3rd parameter between 1st and 2nd
		occlusion       += (sampleDepth >= samplePos.z + bias ? 1.0f : 0.0f) * rangeCheck;
	}
	occlusion = 1.0f - (occlusion / kernelSize);

	FragColor = occlusion;
}
