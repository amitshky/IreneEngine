#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture> textures)
{
	m_VAO = std::make_shared<VertexArray>();
	m_VBO = std::make_shared<VertexBuffer>(vertices);
	m_EBO = std::make_shared<IndexBuffer>(indices, indices.size());

	Init();
}

void Mesh::Draw(std::shared_ptr<Shader>& shader)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

		shader->SetInt((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		//m_Textures[i].Bind();
	}

	// draw mesh
	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	m_VAO->Unbind();

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
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
