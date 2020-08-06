#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"

namespace myo {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model = glm::mat4(1.0f));
		static void Submit(const Ref<Shader>& shader, uint32_t count, const glm::mat4& model = glm::mat4(1.0f));

	private:
		struct SceneData
		{
			glm::mat4 m_ViewProjectionMatrix;
		};
		static Scope<SceneData> s_SceneData;
	};

}
