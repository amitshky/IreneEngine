#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "My_OpenGL/Renderer/Buffer.h"
#include "My_OpenGL/Renderer/Camera.h"
#include "My_OpenGL/Renderer/Shader.h"
#include "My_OpenGL/Renderer/Texture.h"
#include "My_OpenGL/Renderer/VertexArray.h"

#include "imgui.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "examples/imgui_impl_opengl3.cpp"
#include "examples/imgui_impl_glfw.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void ImGuiAttach(GLFWwindow* window);
void ImGuiDettach();
void ImGuiBegin();
void ImGuiEnd();

// settings
const unsigned int SCR_HEIGHT = 720;
const unsigned int SCR_WIDTH = (int)(SCR_HEIGHT * (16.0f / 9.0f));

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool ALTPressFlag = false;

glm::vec3 lightPos(1.0f, 1.0f, 1.5f);

int main()
{
	Log::Init();
	// glfw: initialize and configure
	glfwInit();

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	CORE_INFO("OpenGL Info:");
	CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
	CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
	CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
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

	glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};

	std::shared_ptr<VertexArray> CubeVA = std::make_shared<VertexArray>();
	std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	vbo->SetLayout({
		{ShaderDataType::Float3, "a_Position"},
		{ShaderDataType::Float3, "a_Normal"},
		{ShaderDataType::Float2, "a_TexCoords"}
	});
	CubeVA->AddVertexBuffer(vbo);
	
	// Shader
	//std::shared_ptr<Shader> CubeShader = std::make_shared<Shader>("assets/shaders/3DCubeTexture.shader");
	std::shared_ptr<Shader> CubeShader = std::make_shared<Shader>("assets/shaders/BasicLighting.shader");
	//std::shared_ptr<Shader> CubeShader = std::make_shared<Shader>("assets/shaders/MultipleLights.shader");

	// Lighting Maps
	CubeShader->Bind();
	std::shared_ptr<Texture2D> diffuseMap = std::make_shared<Texture2D>("assets/textures/container2.png");
	CubeShader->SetInt("u_Material.diffuse", 0);
	std::shared_ptr<Texture2D> specularMap = std::make_shared<Texture2D>("assets/textures/container2_specular.png");
	CubeShader->SetInt("u_Material.specular", 1);

	// Light Intensity attenuation values
	CubeShader->SetFloat("u_Light.constant", 1.0f);
	CubeShader->SetFloat("u_Light.linear", 0.09f);
	CubeShader->SetFloat("u_Light.quadratic", 0.032f);

	vbo->Unbind();
	CubeVA->Unbind();
	CubeShader->Unbind();

	// Lamp object
	/*std::shared_ptr<VertexArray> LampVA = std::make_shared<VertexArray>();
	LampVA->AddVertexBuffer(vbo);
	std::shared_ptr<Shader> LampShader = std::make_shared<Shader>("assets/shaders/Light.shader");
	vbo->Unbind();
	LampVA->Unbind();
	LampShader->Unbind();*/

	// Phong Lighting component's intensity
	glm::vec3 diffuseColor = glm::vec3(0.8f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
	glm::vec3 specularColor = glm::vec3(1.0f);

	ImGuiAttach(window);
	
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(window);

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//lightPos.x = sin(glfwGetTime() * 2.0f);
		//lightPos.y = sin(glfwGetTime());
		//lightPos.z = cos(glfwGetTime() * 2.0f);

		// view/projection transformation
		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		// world coordinates
		glm::mat4 model;

		// Cube object
		CubeShader->Bind();
		CubeShader->SetFloat3("u_ViewPos", camera.GetPosition());
		//------------BasicLighting------------------//
		{
			// light properties
			//CubeShader->SetFloat3("u_Light.position", lightPos);	// for point light
			CubeShader->SetFloat3("u_Light.position", camera.GetPosition());	// for spot light
			CubeShader->SetFloat3("u_Light.direction", camera.GetFront());
			CubeShader->SetFloat("u_Light.cutOff", glm::cos(glm::radians(20.5f)));
			CubeShader->SetFloat("u_Light.outerCutOff", glm::cos(glm::radians(27.5f)));
			CubeShader->SetFloat3("u_Light.ambient", ambientColor);
			CubeShader->SetFloat3("u_Light.diffuse", diffuseColor);
			CubeShader->SetFloat3("u_Light.specular", specularColor);
		}

		//------------Multiple Lights----------------//
		{
			//// directional light
			//CubeShader->SetFloat3("u_DirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
			//CubeShader->SetFloat3("u_DirLight.ambient", ambientColor);
			//CubeShader->SetFloat3("u_DirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
			//CubeShader->SetFloat3("u_DirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
			//// point light 1
			//CubeShader->SetFloat3("u_PointLight[0].position", pointLightPositions[0]);
			//CubeShader->SetFloat3("u_PointLight[0].ambient", ambientColor);
			//CubeShader->SetFloat3("u_PointLight[0].diffuse", diffuseColor);
			//CubeShader->SetFloat3("u_PointLight[0].specular", specularColor);
			//CubeShader->SetFloat("u_PointLight[0].constant", 1.0f);
			//CubeShader->SetFloat("u_PointLight[0].linear", 0.09);
			//CubeShader->SetFloat("u_PointLight[0].quadratic", 0.032);
			//// point light 2
			//CubeShader->SetFloat3("u_PointLight[1].position", pointLightPositions[1]);
			//CubeShader->SetFloat3("u_PointLight[1].ambient", ambientColor);
			//CubeShader->SetFloat3("u_PointLight[1].diffuse", diffuseColor);
			//CubeShader->SetFloat3("u_PointLight[1].specular", specularColor);
			//CubeShader->SetFloat("u_PointLight[1].constant", 1.0f);
			//CubeShader->SetFloat("u_PointLight[1].linear", 0.09);
			//CubeShader->SetFloat("u_PointLight[1].quadratic", 0.032);
			//// point light 3
			//CubeShader->SetFloat3("u_PointLight[2].position", pointLightPositions[2]);
			//CubeShader->SetFloat3("u_PointLight[2].ambient", ambientColor);
			//CubeShader->SetFloat3("u_PointLight[2].diffuse", diffuseColor);
			//CubeShader->SetFloat3("u_PointLight[2].specular", specularColor);
			//CubeShader->SetFloat("u_PointLight[2].constant", 1.0f);
			//CubeShader->SetFloat("u_PointLight[2].linear", 0.09);
			//CubeShader->SetFloat("u_PointLight[2].quadratic", 0.032);
			//// point light 4
			//CubeShader->SetFloat3("u_PointLight[3].position", pointLightPositions[3]);
			//CubeShader->SetFloat3("u_PointLight[3].ambient", ambientColor);
			//CubeShader->SetFloat3("u_PointLight[3].diffuse", diffuseColor);
			//CubeShader->SetFloat3("u_PointLight[3].specular", specularColor);
			//CubeShader->SetFloat("u_PointLight[3].constant", 1.0f);
			//CubeShader->SetFloat("u_PointLight[3].linear", 0.09);
			//CubeShader->SetFloat("u_PointLight[3].quadratic", 0.032);
			//// SpotLight
			//CubeShader->SetFloat3("u_SpotLight.position", camera.GetPosition());
			//CubeShader->SetFloat3("u_SpotLight.direction", camera.GetFront());
			//CubeShader->SetFloat3("u_SpotLight.ambient", ambientColor);
			//CubeShader->SetFloat3("u_SpotLight.diffuse", diffuseColor);
			//CubeShader->SetFloat3("u_SpotLight.specular", specularColor);
			//CubeShader->SetFloat("u_SpotLight.constant", 1.0f);
			//CubeShader->SetFloat("u_SpotLight.linear", 0.09);
			//CubeShader->SetFloat("u_SpotLight.quadratic", 0.032);
			//CubeShader->SetFloat("u_SpotLight.cutOff", glm::cos(glm::radians(12.5f)));
			//CubeShader->SetFloat("u_SpotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		}

		// material properties
		CubeShader->SetFloat("u_Material.shininess", 64.0f);

		CubeShader->SetMat4("u_Projection", projection);
		CubeShader->SetMat4("u_View", view);

		diffuseMap->Bind();
		specularMap->Bind(1);

		CubeVA->Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			CubeShader->SetMat4("u_Model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Lamp object

		//LampShader->Bind();
		//LampShader->SetMat4("u_Projection", projection);
		//LampShader->SetMat4("u_View", view);
		//LampVA->Bind();
		//for (unsigned int i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1.0f);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
		//	LampShader->SetMat4("u_Model", model);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		//glDrawElements(GL_TRIANGLES, SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	ImGuiDettach();
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	// Press esc to close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::PITCHUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::PITCHDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::YAWLEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::YAWRIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ImGuiAttach(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiDettach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiBegin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiEnd()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)SCR_WIDTH, (float)SCR_HEIGHT);
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
