#pragma once

#ifdef PLATFORM_WINDOWS

extern irene::Application* irene::CreateApplication();

int main(int argc, char** argv)
{
	irene::Log::Init();

	auto app = irene::CreateApplication();
	app->Run();
	delete app;
}

#endif
