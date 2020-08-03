#pragma once

#include "My_OpenGL/Core/Layer.h"
#include "My_OpenGL/Events/KeyEvent.h"
#include "My_OpenGL/Events/MouseEvent.h"
#include "My_OpenGL/Events/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace myo {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
