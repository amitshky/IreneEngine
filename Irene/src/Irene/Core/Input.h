#pragma once

#include "Irene/Core/Core.h"

namespace irene {

	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsKeyReleased(int keycode);

		static bool IsMouseButtonPressed(int button);
		static bool IsMouseButtonReleased(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
