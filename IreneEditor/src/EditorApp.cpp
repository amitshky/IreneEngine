#include <Irene.h>
#include <Irene/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace irene {

	class Sandbox : public Application
	{
	public:
		Sandbox()
		{
			PushLayer(new EditorLayer());
		}
		~Sandbox() {}

	};

	Application* CreateApplication()
	{
		return new Sandbox();
	}

}

