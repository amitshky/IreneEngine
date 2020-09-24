#include "pch.h"
#include "Renderer3D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace irene {

	struct Renderer3DData
	{
		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;

		Ref<VertexArray> PlaneVertexArray;
		Ref<VertexBuffer> PlaneVertexBuffer;

		Ref<Texture2D> WhiteTexture;

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

		// Cube
		s_Data.CubeVertexArray = VertexArray::Create();
		s_Data.CubeVertexBuffer = VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
		s_Data.CubeVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"}
		});
		s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);
		s_Data.CubeVertexBuffer->Unbind();
		s_Data.CubeVertexArray->Unbind();

		// Plane
		s_Data.PlaneVertexArray = VertexArray::Create();
		s_Data.PlaneVertexBuffer = VertexBuffer::Create(planeVertices, sizeof(planeVertices));
		s_Data.PlaneVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"}
		});
		s_Data.PlaneVertexArray->AddVertexBuffer(s_Data.PlaneVertexBuffer);
		s_Data.PlaneVertexBuffer->Unbind();
		s_Data.PlaneVertexArray->Unbind();

		// White texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);		// creates a 1x1 white texture
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// Shaders
		s_Data.TextureShader = Shader::Create("assets/shaders/texture.shader");
		s_Data.LightingShader = Shader::Create("assets/shaders/BasicLighting.shader");

		s_Data.LightingShader->Bind();
		s_Data.LightingShader->SetInt("u_Material.diffuse", 0);
		s_Data.LightingShader->SetInt("u_Material.specular", 1);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);

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
	}

	void Renderer3D::EndScene()
	{
	}

	void Renderer3D::DrawPlane(const glm::mat4& transform, const glm::vec4& color)
	{
		const float textureTile = 1.0f;

		s_Data.TextureShader->Bind();
		s_Data.PlaneVertexArray->Bind();
		s_Data.WhiteTexture->Bind();

		s_Data.TextureShader->SetMat4("u_Model", transform);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);
		s_Data.TextureShader->SetFloat4("u_Color", color);

		RenderCommand::Draw(6);
		s_Data.PlaneVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawPlane(const glm::mat4& transform, const Ref<Texture2D>& texture, float textureTile)
	{
		const glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		s_Data.TextureShader->Bind();
		s_Data.PlaneVertexArray->Bind();
		texture->Bind();

		s_Data.TextureShader->SetMat4("u_Model", transform);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);
		s_Data.TextureShader->SetFloat4("u_Color", color);

		RenderCommand::Draw(6);
		s_Data.PlaneVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawPlane(const glm::mat4& transform, const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData)
	{
		s_Data.LightingShader->Bind();
		s_Data.PlaneVertexArray->Bind();

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
		s_Data.LightingShader->SetMat4("u_Model", transform);

		RenderCommand::Draw(6);
		s_Data.PlaneVertexArray->Unbind();
		s_Data.LightingShader->Unbind();
	}

	void Renderer3D::DrawPlane(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis, const glm::vec4& color)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
						* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
						* glm::scale(glm::mat4(1.0f), scale);
		DrawPlane(model, color);
	}

	void Renderer3D::DrawPlane(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis, 
		const Ref<Texture2D>& texture, float textureTile)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
						* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
						* glm::scale(glm::mat4(1.0f), scale);
		DrawPlane(model, texture, textureTile);
	}

	void Renderer3D::DrawPlane(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis,
		const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
						* glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
						* glm::scale(glm::mat4(1.0f), scale);
		DrawPlane(model, diffuseTex, specularTex, lightData);
	}

	///////////////////////////////////
	
	void Renderer3D::DrawCube(const glm::mat4& transform, const glm::vec4& color)
	{
		const float textureTile = 1.0f;

		s_Data.TextureShader->Bind();
		s_Data.CubeVertexArray->Bind();
		s_Data.WhiteTexture->Bind();

		s_Data.TextureShader->SetMat4("u_Model", transform);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);
		s_Data.TextureShader->SetFloat4("u_Color", color);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawCube(const glm::mat4& transform, const Ref<Texture2D>& texture, float textureTile)
	{
		const glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		s_Data.TextureShader->Bind();
		s_Data.CubeVertexArray->Bind();
		texture->Bind();

		s_Data.TextureShader->SetMat4("u_Model", transform);
		s_Data.TextureShader->SetFloat("u_Tile", textureTile);
		s_Data.TextureShader->SetFloat4("u_Color", color);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.TextureShader->Unbind();
	}

	void Renderer3D::DrawCube(const glm::mat4& transform, const Ref<Texture2D>& diffuseTex, const Ref<Texture2D>& specularTex, const LightData& lightData)
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
		s_Data.LightingShader->SetMat4("u_Model", transform);

		RenderCommand::Draw(36);
		s_Data.CubeVertexArray->Unbind();
		s_Data.LightingShader->Unbind();
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			  * glm::scale(glm::mat4(1.0f), scale);
		DrawCube(model, color);
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture2D>& texture, float textureTile)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			  * glm::scale(glm::mat4(1.0f), scale);
		DrawCube(model, texture, textureTile);
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture2D>& diffuseTex, 
		const Ref<Texture2D>& specularTex, const LightData& lightData)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), position)
			  * glm::scale(glm::mat4(1.0f), scale);
		DrawCube(model, diffuseTex, specularTex, lightData);
	}

}