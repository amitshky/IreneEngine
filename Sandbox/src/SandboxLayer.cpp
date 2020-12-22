#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SandboxLayer.h"


SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f)
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	// positions
	glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
	glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);  
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;
	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


	float quadVertices[] = {
		// positions            // normal         // texcoords  // tangent                          // bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};

	m_VA = irene::VertexArray::Create();
	m_VB = irene::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	m_VB->SetLayout({
		{irene::ShaderDataType::Float3, "a_Position"},
		{irene::ShaderDataType::Float3, "a_Normal"},
		{irene::ShaderDataType::Float2, "a_TexCoords"},
		{irene::ShaderDataType::Float3, "a_Tangent"},
		{irene::ShaderDataType::Float3, "a_Bitangent"}
	});
	m_VA->AddVertexBuffer(m_VB);
	m_VB->Unbind();
	m_VA->Unbind();

	m_Shader = irene::Shader::Create("assets/shaders/normalMap.shader");

	m_DiffuseMap  = irene::Texture2D::Create("assets/textures/bricks/Bricks01_COL_VAR1_3K.jpg");
	m_SpecularMap = irene::Texture2D::Create("assets/textures/bricks/Bricks01_GLOSS_3K.jpg");
	m_NormalMap   = irene::Texture2D::Create("assets/textures/bricks/Bricks01_NRM_3K.jpg");
	m_HeightMap   = irene::Texture2D::Create("assets/textures/bricks/Bricks01_DISP_3K_INV.jpg"); // should be inverse of a normal displacement map because we are calculating for depth not height

	m_Shader->Bind();
	m_Shader->SetInt("u_Material.diffuse", 0);
	m_Shader->SetInt("u_Material.specular", 1);
	m_Shader->SetInt("u_Material.normal", 2);
	m_Shader->SetInt("u_Material.height", 3);

	constexpr glm::vec3 position(0.0f, 0.0f, -1.0f);
	constexpr glm::vec3 scale(1.0f);
	constexpr glm::vec3 rotationAxis(1.0f, 0.0f, 0.0f);
	constexpr float rotation = glm::radians(0.0f);
	m_LightPos = glm::vec3(-0.3f, 0.3f, -0.8f);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
		* glm::scale(glm::mat4(1.0f), scale);
	m_Shader->SetMat4("u_Model", model);
	m_Shader->SetFloat3("u_LightPos", m_LightPos);
	m_Shader->SetFloat("u_HeightScale", 0.05f);
	m_Shader->Unbind();
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	
	glm::mat4 viewProj = m_CameraController.GetCamera().GetViewProjectionMatrix();

	m_VA->Bind();
	m_Shader->Bind();

	m_DiffuseMap->Bind();
	m_SpecularMap->Bind(1);
	m_NormalMap->Bind(2);
	m_HeightMap->Bind(3);
	
	m_Shader->SetMat4("u_ViewProjection", viewProj);
	m_Shader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	irene::RenderCommand::Draw(6);
	m_Shader->Unbind();
	m_VA->Unbind();
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}

