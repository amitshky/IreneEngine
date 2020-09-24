#include <Irene.h>
#include <Irene/Core/EntryPoint.h>

#include "SandboxLayer.h"

class Sandbox : public irene::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}
	~Sandbox() {}

};

irene::Application* irene::CreateApplication()
{
	return new Sandbox();
}