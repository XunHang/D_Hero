#pragma once

#include "DHero/Core/Layer.h"
#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Events/KeyEvent.h"
#include "DHero/Events/MouseEvent.h"


namespace DH {
	class DH_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void begin();
		void end();


	private:
	};
}