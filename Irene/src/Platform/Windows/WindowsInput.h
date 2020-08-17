#pragma once

#include "Irene/Core/Input.h"

namespace irene {

	class WindowsInput : public Input
	{
	public:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsKeyReleasedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual bool IsMouseButtonReleasedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}
