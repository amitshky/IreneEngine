#pragma once

#include "Irene/Core/Window.h"
#include "Irene/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace irene {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};

}
