#include "ExampleLayer.h"

#include <GLFW/glfw3.h>

ExampleLayer::ExampleLayer()
	: Layer("Example"), camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Depth testing
	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
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

	/// Cube Vertex Array
	CubeVA = myo::CreateRef<myo::VertexArray>();
	vbo = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	vbo->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normal"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
		});
	CubeVA->AddVertexBuffer(vbo);

	/// Shader
	CubeShader = myo::CreateRef<myo::Shader>("assets/shaders/MultipleLights.shader");

	/// Lamp object
	LampVA = myo::CreateRef<myo::VertexArray>();
	LampVA->AddVertexBuffer(vbo);
	LampShader = myo::CreateRef<myo::Shader>("assets/shaders/Light.shader");
	vbo->Unbind();
	LampVA->Unbind();
	LampShader->Unbind();

	/// Phong Lighting component's intensity
	diffuseColor = glm::vec3(0.8f) * 3.0f; // decrease the influence
	ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
	specularColor = glm::vec3(1.0f);

	/// Model loading
	nanosuitShader = myo::CreateRef<myo::Shader>("assets/shaders/ModelLoading.shader");
	nanosuitModel = myo::CreateRef<myo::Model>("assets/3DModels/nanosuit/nanosuit.obj");
}

void ExampleLayer::OnUpdate(myo::Timestep ts)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(m_BgColor.x, m_BgColor.y, m_BgColor.z, m_BgColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Light position	// use this to rotate a point light source
	lightPos.x = sin(glfwGetTime() * 2.0f);
	lightPos.y = sin(glfwGetTime());
	lightPos.z = cos(glfwGetTime() * 2.0f);

	// view/projection transformation
	glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 16.0f / 9.0f, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	// world coordinates
	glm::mat4 model;

	CubeShader->Bind();

	/// Model Loading

	LampShader->Bind();
	LampShader->SetMat4("u_Projection", projection);
	LampShader->SetMat4("u_View", view);
	LampVA->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
	LampShader->SetMat4("u_Model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	nanosuitShader->Bind();
	nanosuitShader->SetFloat3("u_ViewPos", camera.GetPosition());
	//nanosuitShader->SetFloat3("u_Light.position", camera.GetPosition());	// for spot light
	nanosuitShader->SetFloat3("u_Light.position", lightPos);				// for point light
	nanosuitShader->SetFloat3("u_Light.direction", camera.GetFront());
	nanosuitShader->SetFloat("u_Light.cutOff", glm::cos(innerCutOff));
	nanosuitShader->SetFloat("u_Light.outerCutOff", glm::cos(outerCutOff));
	nanosuitShader->SetFloat3("u_Light.ambient", ambientColor);
	nanosuitShader->SetFloat3("u_Light.diffuse", diffuseColor);
	nanosuitShader->SetFloat3("u_Light.specular", specularColor);
	nanosuitShader->SetFloat("u_Light.constant", 1.0f);
	nanosuitShader->SetFloat("u_Light.linear", 0.09f);
	nanosuitShader->SetFloat("u_Light.quadratic", 0.032f);
	nanosuitShader->SetMat4("u_Projection", projection);
	nanosuitShader->SetMat4("u_View", view);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f));
	nanosuitShader->SetMat4("u_Model", model);

	nanosuitModel->Draw(nanosuitShader);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BgColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(myo::Event& e)
{
}
