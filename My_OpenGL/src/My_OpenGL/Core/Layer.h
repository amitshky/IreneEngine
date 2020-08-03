#pragma once

#include "My_OpenGL/Core/Core.h"
#include "My_OpenGL/Events/Event.h"

#include "My_OpenGL/Core/Timestep.h"

namespace myo {

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
