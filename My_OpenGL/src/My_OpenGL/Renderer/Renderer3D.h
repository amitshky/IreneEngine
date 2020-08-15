#pragma once

#include "Camera.h"
#include "Texture.h"

namespace myo {

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

		static void DrawColoredPlane(const glm::vec3& color, const glm::vec3& position = glm::vec3(0.0f), float rotation = 0.0f,
			const glm::vec3& rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), const glm::vec3& scale = glm::vec3(1.0f));

		static void DrawTexturedPlane(const Ref<Texture2D>& texture, const glm::vec3& position = glm::vec3(0.0f), float rotation = 0.0f, 
			const glm::vec3& rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), const glm::vec3& scale = glm::vec3(1.0f), float textureTile = 1.0f);

		static void DrawColoredCube(const glm::vec3& color, const glm::vec3& position = glm::vec3(0.0f),
			const glm::vec3& scale = glm::vec3(1.0f));

		static void DrawTexturedCube(const Ref<Texture2D>& texture, const glm::vec3& position = glm::vec3(0.0f), 
			const glm::vec3& scale = glm::vec3(1.0f), float textureTile = 1.0f);

		static void DrawCubeWithLighting(const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData, 
			const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
	};

}
