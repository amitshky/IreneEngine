#include "pch.h"
#include "Mesh.h"

namespace irene {

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture2D>>& textures)
	{
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(vertices);
		m_EBO = IndexBuffer::Create(indices, indices.size());
		m_Textures = textures;

		Init();
	}

	void Mesh::Init()
	{
		m_VBO->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"},
			{ShaderDataType::Float3, "a_Tangent"},
			{ShaderDataType::Float3, "a_Bitangent"}
		});
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);
		m_VAO->Unbind();
	}

	void Mesh::Draw(Ref<Shader>& shader, const glm::mat4& model)
	{
		// bind appropriate textures
		uint32_t diffuseNr = 1;
		uint32_t specularNr = 1;
		uint32_t normalNr = 1;
		uint32_t heightNr = 1;
		for (uint32_t i = 0; i < m_Textures.size(); i++)
		{
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = m_Textures[i]->GetType();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer uint32_t to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer uint32_t to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer uint32_t to stream

			shader->SetInt((name + number).c_str(), i);
			m_Textures[i]->Bind(i);
		}

		// draw mesh
		m_VAO->Bind();
		Renderer::Submit(shader, m_VAO, model);
		m_VAO->Unbind();
	}
	
}
