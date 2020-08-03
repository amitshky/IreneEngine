#include <My_OpenGL.h>
#include <My_OpenGL/Core/EntryPoint.h>

#include "ExampleLayer.h"

class Sandbox : public myo::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

};

myo::Application* myo::CreateApplication()
{
	return new Sandbox();
}