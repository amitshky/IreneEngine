#pragma once

#include "Irene/Core/Core.h"
#include "Irene/Events/Event.h"

#include "Irene/Core/Timestep.h"

namespace irene {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		
		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};

}
