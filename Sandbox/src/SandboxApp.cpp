#include <My_OpenGL.h>
#include <My_OpenGL/Core/EntryPoint.h>

#include "NanosuitLayer.h"

class Sandbox : public myo::Application
{
public:
	Sandbox()
	{
		PushLayer(new NanosuitLayer());
	}
	~Sandbox() {}

};

myo::Application* myo::CreateApplication()
{
	return new Sandbox();
}