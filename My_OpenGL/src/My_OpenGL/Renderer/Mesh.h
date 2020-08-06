#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

// Vertex struct defined in Buffer.h
namespace myo {

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture2D>>& textures);
		void Draw(Ref<Shader>& shader, const glm::mat4& model);
		~Mesh() {}

	private:
		void Init();

	private:
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_EBO;
		std::vector<Ref<Texture2D>> m_Textures;
	};

}
