#pragma once

#include "Core.h"
#include "Events/Event.h"

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

