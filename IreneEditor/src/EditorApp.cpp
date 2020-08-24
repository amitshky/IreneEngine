#include <Irene.h>
#include <Irene/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace irene {

	class EditorApp : public Application
	{
	public:
		EditorApp()
			: Application("Irene Editor App")
		{
			PushLayer(new EditorLayer());
		}
		~EditorApp() {}

	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}

}

