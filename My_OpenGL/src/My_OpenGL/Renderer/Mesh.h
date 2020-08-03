#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"

// Vertex struct defined in Buffer.h
namespace myo {

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<std::shared_ptr<Texture2D>>& textures);
		void Draw(std::shared_ptr<Shader>& shader);
		~Mesh() {}

	private:
		void Init();

	private:
		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_EBO;
		std::vector<std::shared_ptr<Texture2D>> m_Textures;
	};

}
