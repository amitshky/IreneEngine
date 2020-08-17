#pragma once

#include "Irene/Core/Layer.h"
#include "Irene/Events/KeyEvent.h"
#include "Irene/Events/MouseEvent.h"
#include "Irene/Events/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace irene {

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
