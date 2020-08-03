#pragma once

#ifdef PLATFORM_WINDOWS

extern myo::Application* myo::CreateApplication();

int main(int argc, char** argv)
{
	myo::Log::Init();

	auto app = myo::CreateApplication();
	app->Run();
	delete app;
}

#endif
