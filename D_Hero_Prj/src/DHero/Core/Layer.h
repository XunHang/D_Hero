#pragma once

#include "Core.h"
#include "DHero/Events/Event.h"
#include "TimeStep.h"

namespace DH {
	class DH_API Layer	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(TimeStep&) {};
		virtual void OnImGuiRender() {};

		virtual void OnEvent(Event& e) {};

		inline std::string GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}

