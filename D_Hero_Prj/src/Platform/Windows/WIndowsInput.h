#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Core/Input.h"


namespace DH {
	class DH_API WindowsInput :public Input {
	public:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}