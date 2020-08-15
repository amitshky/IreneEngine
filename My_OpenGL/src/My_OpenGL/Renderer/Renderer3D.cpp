#include "pch.h"
#include "Renderer3D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace myo {

	struct Renderer3DData
	{
		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;

		Ref<VertexArray> PlaneVertexArray;
		Ref<VertexBuffer> PlaneVertexBuffer;

		Ref<Shader> ColorShader;
		Ref<Shader> TextureShader;
		Ref<Shader> LightingShader;
	};

	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		float cubeVertices[] = {
		// positions			// normals				// texture coords
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f
		};

		float planeVertices[] = {
			// positions			// normals				// texture coords
			-0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,
			 0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 1.0f,  0.0f,
			 0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
			 0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
			-0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 0.0f,  1.0f,
			-0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,
		};

		/// Cube
		s_Data.CubeVertexArray = CreateRef<VertexArray>();
		s_Data.CubeVertexBuffer = CreateRef<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
		s_Data.CubeVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"}
		});
		s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);
		s_Data.CubeVertexBuffer->Unbind();
		s_Data.CubeVertexArray->Unbind();

		/// Plane
		s_Data.PlaneVertexArray = CreateRef<VertexArray>();
		s_Data.PlaneVertexBuffer = CreateRef<VertexBuffer>(planeVertices, sizeof(planeVertices));
		s_Data.PlaneVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"}
		});
		s_Data.PlaneVertexArray->AddVertexBuffer(s_Data.PlaneVertexBuffer);
		s_Data.PlaneVertexBuffer->Unbind();
		s_Data.PlaneVertexArray->Unbind();

		/// Shaders
		s_Data.ColorShader = CreateRef<Shader>("assets/shaders/Color.shader");
		s_Data.TextureShader = CreateRef<Shader>("assets/shaders/texture.shader");
		s_Data.LightingShader = CreateRef<Shader>("assets/shaders/BasicLighting.shader");

		s_Data.LightingShader->Bind();
		s_Data.LightingShader->SetInt("u_Material.diffuse", 0);
		s_Data.LightingShader->SetInt("u_Material.specular", 1);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);

		s_Data.ColorShader->Unbind();
		s_Data.LightingShader->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::Shutdown()
	{
	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
		s_Data.LightingShader->Bind();
		s_Data.LightingShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data.LightingShader->SetFloat3("u_ViewPos", camera.GetPosition());
		
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data.ColorShader->Bind();
		s_Data.ColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer3D::EndScene()
	{
	}

	void Renderer3D::DrawColoredPlane(const glm::vec3& color, const glm::vec3& position, float rotation, const glm::vec3& rotationAxis, const glm::vec3& scale)
	{
		s_Data.ColorShader->Bind();
		s_Data.PlaneVertexArray->Bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
			* glm::scale(glm::mat4(1.0f), scale);

		s_Data.ColorShader->SetMat4("u_Model", model);
		s_Data.ColorShader->SetFloat3("u_Color", color);
		
		RenderCommand::Draw(36);
		s_Data.PlaneVertexArray->Unbind();
		s_Data.ColorShader->Unbind();
	}

	void Renderer3D::DrawTexturedPlane(const Ref<Texture2D>& texture, const glm::vec3& position, float rotation, const glm::vec3& rotationAxis, 
		const glm::vec3& scale, float textureTile)
	{
		s_Data.TextureShader->Bind();
		s_Data.PlaneVertexArray->Bind();
		texture->Bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
			* glm::scale(glm::mat4(1.0f), scale);

		s_Data.TextureShader->SetMat4("u_Model", model);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);

		RenderCommand::Draw(36);
		s_Data.PlaneVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawColoredCube(const glm::vec3& color, const glm::vec3& position, const glm::vec3& scale)
	{
		s_Data.ColorShader->Bind();
		s_Data.CubeVertexArray->Bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), scale);

		s_Data.ColorShader->SetMat4("u_Model", model);
		s_Data.ColorShader->SetFloat3("u_Color", color);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawTexturedCube(const Ref<Texture2D>& texture, const glm::vec3& position, const glm::vec3& scale, float textureTile)
	{
		s_Data.TextureShader->Bind();
		s_Data.CubeVertexArray->Bind();
		texture->Bind();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position) 
			* glm::scale(glm::mat4(1.0f), scale);

		s_Data.TextureShader->SetMat4("u_Model", model);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawCubeWithLighting(const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData,
		const glm::vec3& position, const glm::vec3& scale)
	{
		s_Data.LightingShader->Bind();
		s_Data.CubeVertexArray->Bind();

		diffuseTex->Bind();
		specularTex->Bind(1);

		s_Data.LightingShader->SetFloat3("u_Light.position", lightData.LightPos);
		s_Data.LightingShader->SetFloat3("u_Light.ambient", lightData.AmbientColor);
		s_Data.LightingShader->SetFloat3("u_Light.diffuse", lightData.DiffuseColor);
		s_Data.LightingShader->SetFloat3("u_Light.specular", lightData.SpecularColor);
		s_Data.LightingShader->SetFloat("u_Light.constant", lightData.ConstantAttenuation);
		s_Data.LightingShader->SetFloat("u_Light.linear", lightData.LinearAttenuation);
		s_Data.LightingShader->SetFloat("u_Light.quadratic", lightData.QuadraticAttenuation);

		s_Data.LightingShader->SetFloat("u_Material.shininess", 64.0f);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), scale);
		s_Data.LightingShader->SetMat4("u_Model", model);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.LightingShader->Unbind();
	}

}