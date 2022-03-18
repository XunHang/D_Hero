#pragma once

#include "DHero/Layer.h"

namespace DH {
	class DH_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	protected:

	private:
	};
}