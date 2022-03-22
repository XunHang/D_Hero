#pragma once

#include "DHero/Core.h"


namespace DH {

	class DH_API GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	protected:

	private:

	};

}