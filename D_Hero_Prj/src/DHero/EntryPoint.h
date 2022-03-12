#pragma once

#ifdef DH_PLATFORM_WINDOWS

#include "Application.h"

extern DH::Application* DH::CreaterApplication();

int main(int argv, char** argc) {
	auto app = DH::CreaterApplication();
	app->Run();
	delete app;
}

#else
	#error Please Define Platform.(Only support Windows)
#endif