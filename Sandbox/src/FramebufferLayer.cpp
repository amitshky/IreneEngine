#include <GLFW/glfw3.h>
#include "FramebufferLayer.h"

FramebufferLayer::FramebufferLayer()
	: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions	// texCoords
		-1.0f,  1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f,  1.0f,	0.0f, 1.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f
	};

	m_ScreenShader = irene::Shader::Create("assets/shaders/FramebufferScreen.shader");

	m_CubeTexture = irene::Texture2D::Create("assets/textures/container.jpg");
	m_PlaneTexture = irene::Texture2D::Create("assets/textures/wall.jpg");

	// Quad
	m_QuadVA = irene::VertexArray::Create();
	m_QuadVB = irene::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	m_QuadVB->SetLayout({
		{irene::ShaderDataType::Float2, "a_Position"},
		{irene::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_QuadVA->AddVertexBuffer(m_QuadVB);
	m_QuadVB->Unbind();
	m_QuadVA->Unbind();

	m_ScreenShader->SetInt("u_ScreenTexture", 0);
}

FramebufferLayer::~FramebufferLayer()
{
}

void FramebufferLayer::OnAttach()
{
	irene::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_Framebuffer = irene::Framebuffer::Create(fbSpec);
}

void FramebufferLayer::OnDetach()
{
}

void FramebufferLayer::OnUpdate(irene::Timestep ts)
{
	m_Framebuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());

	irene::Renderer3D::DrawTexturedCube(m_CubeTexture, { -1.0f, 0.0f, -1.0f }, glm::vec3(1.0f));
	irene::Renderer3D::DrawTexturedCube(m_CubeTexture, { 2.0f, 0.0f, 0.0f }, glm::vec3(1.0f));
	irene::Renderer3D::DrawTexturedPlane(m_PlaneTexture, { 0.0f, -0.5001f, 0.0f }, 1.5708f, { 1.0f, 0.0f, 0.0f }, glm::vec3(8.0f), 2.0f);

	m_Framebuffer->Unbind();
	glDisable(GL_DEPTH_TEST);

	irene::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT);

	m_ScreenShader->Bind();
	m_QuadVA->Bind();
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	irene::Renderer3D::EndScene();
}

void FramebufferLayer::OnImGuiRender()
{
	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = false;
	if (dockingEnabled)
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
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
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

				if (ImGui::MenuItem("Exit")) irene::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void FramebufferLayer::OnEvent(irene::Event& e)
{
	irene::WindowResizeEvent* resizeEvent = dynamic_cast<irene::WindowResizeEvent*>(&e);
	if (resizeEvent)
		m_Framebuffer->Resize(resizeEvent->GetWidth(), resizeEvent->GetHeight());

	m_CameraController.OnEvent(e);
}
