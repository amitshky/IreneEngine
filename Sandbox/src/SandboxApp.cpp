#include <My_OpenGL.h>
#include <My_OpenGL/Core/EntryPoint.h>

//#include "NanosuitLayer.h"
//#include "CubeLayer.h"
#include "BlendingTestLayer.h"

class Sandbox : public myo::Application
{
public:
	Sandbox()
	{
		//PushLayer(new NanosuitLayer());
		//PushLayer(new CubeLayer());
		PushLayer(new BlendingTestLayer());
	}
	~Sandbox() {}

};

myo::Application* myo::CreateApplication()
{
	return new Sandbox();
}