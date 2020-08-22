#pragma once

#include "Core.h"

#include "Window.h"
#include "Irene/Events/Event.h"
#include "Irene/Core/LayerStack.h"
#include "Irene/Events/ApplicationEvent.h"

#include "Irene/Core/Timestep.h"

#include "Irene/ImGui/ImGuiLayer.h"

namespace irene {

	class Application
	{
	public:
		Application(const std::string& name = "Irene Engine");
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		ImGuiLayer* m_ImGuiLayer;
	};

	// defined in a Client
	Application* CreateApplication();

}
