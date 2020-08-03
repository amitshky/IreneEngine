#pragma once

#include "Core.h"

#include "Window.h"
#include "My_OpenGL/Events/Event.h"
//#include "My_OpenGL/Core/LayerStack.h"
#include "My_OpenGL/Events/ApplicationEvent.h"

//#include "My_OpenGL/Core/Timestep.h"

//#include "My_OpenGL/ImGui/ImGuiLayer.h"

namespace myo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		// PushLayer
		// PushOverlay

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		//ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		//LayerStack m_LayerStack;
		//float m_LastFrameTime = 0.0f;
	};

	// defined in a Client
	Application* CreateApplication();

}
