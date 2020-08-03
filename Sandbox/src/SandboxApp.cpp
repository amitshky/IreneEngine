#include <My_OpenGL.h>
#include <My_OpenGL/Core/EntryPoint.h>

class Sandbox : public myo::Application
{
public:
	Sandbox()
	{
		// push layer
	}
	~Sandbox() {}

};

myo::Application* myo::CreateApplication()
{
	return new Sandbox();
}