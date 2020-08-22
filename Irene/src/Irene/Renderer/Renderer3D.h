#pragma once

#include "Camera.h"
#include "Texture.h"

namespace irene {

	struct LightData
	{
		glm::vec3 LightPos;
		glm::vec3 AmbientColor;
		glm::vec3 DiffuseColor;
		glm::vec3 SpecularColor;

		float ConstantAttenuation;
		float LinearAttenuation;
		float QuadraticAttenuation;

		LightData(const glm::vec3& lightPos, const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor,
			float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
			: LightPos(lightPos), AmbientColor(ambientColor), DiffuseColor(diffuseColor),SpecularColor(specularColor), 
			ConstantAttenuation(constant), LinearAttenuation(linear), QuadraticAttenuation(quadratic)
		{}
	};

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		// Plane
		static void DrawPlane(const glm::vec4& color, const glm::vec3& position, float rotation, 
			const glm::vec3& rotationAxis, const glm::vec3& scale);

		static void DrawPlane(const Ref<Texture2D>& texture, const glm::vec3& position, float rotation, 
			const glm::vec3& rotationAxis, const glm::vec3& scale, float textureTile = 1.0f);

		static void DrawPlane(const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData,
			const glm::vec3& position, float rotation, const glm::vec3& rotationAxis, const glm::vec3& scale);


		// Cube
		static void DrawCube(const glm::vec4& color, const glm::vec3& position, const glm::vec3& scale);

		static void DrawCube(const Ref<Texture2D>& texture, const glm::vec3& position, const glm::vec3& scale, float textureTile = 1.0f);

		static void DrawCube(const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData, 
			const glm::vec3& position, const glm::vec3& scale);
	};

}
