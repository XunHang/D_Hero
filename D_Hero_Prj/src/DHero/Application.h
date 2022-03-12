#pragma once

#include "Core.h"

namespace DH {

	class DH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To Do by Client.
	Application* CreaterApplication();

}

