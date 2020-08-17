#include <Irene.h>
#include <Irene/Core/EntryPoint.h>

//#include "NanosuitLayer.h"
//#include "CubeLayer.h"
//#include "BlendingTestLayer.h"
#include "FramebufferLayer.h"

class Sandbox : public irene::Application
{
public:
	Sandbox()
	{
		//PushLayer(new NanosuitLayer());
		//PushLayer(new CubeLayer());
		//PushLayer(new BlendingTestLayer());
		PushLayer(new FramebufferLayer());
	}
	~Sandbox() {}

};

irene::Application* irene::CreateApplication()
{
	return new Sandbox();
}