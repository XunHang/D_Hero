#pragma once

#ifdef DH_PLATFORM_WINDOWS

extern DH::Application* DH::CreaterApplication();

int main(int argv, char** argc) {

	DH::Log::Init();
	DH_CORE_WARN("Init Engine Complete.");
	int numb = 7;
	DH_INFO("Hello D-Hero Numb:{0}", numb);

	auto app = DH::CreaterApplication();
	app->Run();
	delete app;
}
#endif