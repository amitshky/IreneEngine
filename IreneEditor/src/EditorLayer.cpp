#include <GLFW/glfw3.h>
#include "EditorLayer.h"

namespace irene {

	EditorLayer::EditorLayer()
		: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
	{
	}

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		float skyboxVertices[] = {
			// positions
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		m_SkyboxVA = irene::VertexArray::Create();
		m_SkyboxVB = irene::VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
		m_SkyboxVB->SetLayout({
			{ irene::ShaderDataType::Float3, "a_Position" }
		});
		m_SkyboxVA->AddVertexBuffer(m_SkyboxVB);

		m_SkyboxShader = Shader::Create("assets/shaders/Cubemap.shader");
		m_SkyboxShader->SetInt("u_Skybox", 5);
		m_SkyboxVA->Unbind();
		m_SkyboxVB->Unbind();
		m_SkyboxShader->Unbind();

		std::vector<std::string> faces =
		{
			"assets/textures/skybox/right.jpg",
			"assets/textures/skybox/left.jpg",
			"assets/textures/skybox/top.jpg",
			"assets/textures/skybox/bottom.jpg",
			"assets/textures/skybox/front.jpg",
			"assets/textures/skybox/back.jpg"
		};
		m_CubemapTexture = Texture2D::Create(faces);

		m_CubeTexture = Texture2D::Create("assets/textures/container.jpg");
		m_PlaneTexture = Texture2D::Create("assets/textures/wall.jpg");

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_Framebuffer = Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		if (m_ViewportFocused && m_ViewportHovered)
			m_CameraController.OnUpdate(ts);
		
		Renderer3D::BeginScene(m_CameraController.GetCamera());
		Renderer3D::DrawCube(m_CubeTexture, { -1.0f, 0.0f, -1.0f }, glm::vec3(1.0f));
		Renderer3D::DrawCube(m_CubeTexture, { 2.0f, 0.0f, 0.0f }, glm::vec3(1.0f));
		Renderer3D::DrawPlane(m_PlaneTexture, { 0.0f, -0.5001f, 0.0f }, glm::radians(-90.0f), { 1.0f, 0.0f, 0.0f }, glm::vec3(8.0f), 2.0f);
		Renderer3D::EndScene();


		// Render skybox last
		glm::mat4 view = glm::mat4(glm::mat3(m_CameraController.GetCamera().GetViewMatrix()));
		glm::mat4 proj = m_CameraController.GetCamera().GetProjectionMatrix();
		glm::mat4 viewProj = proj * view;
		glDepthFunc(GL_LEQUAL);
		m_SkyboxShader->Bind();
		m_SkyboxShader->SetMat4("u_ViewProjection", viewProj);
		m_SkyboxVA->Bind();
		m_CubemapTexture->Bind(5);
		irene::RenderCommand::Draw(36);
		glDepthFunc(GL_LESS);
		
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		/////////////////////////////////////

		ImGui::Begin("Settings");
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		if (Input::IsMouseButtonPressed(MOUSE_BUTTON_5) && m_ViewportHovered)
			ImGui::SetWindowFocus();
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		ImVec2 viewportPannelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != (*(glm::vec2*)&viewportPannelSize) && viewportPannelSize.x > 0 && viewportPannelSize.y > 0)
		{
			m_Framebuffer->Resize((uint32_t)viewportPannelSize.x, (uint32_t)viewportPannelSize.y);
			m_ViewportSize = { viewportPannelSize.x, viewportPannelSize.y };
			m_CameraController.OnResize(viewportPannelSize.x, viewportPannelSize.y);
		}
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End(); // dockspace
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}

}


