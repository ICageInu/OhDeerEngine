#pragma once
#include <Xinput.h>
#include "Singleton.h"
#include "glm/vec2.hpp"
#include <map>
//https://lcmccauley.wordpress.com/2014/01/05/gamepad-input-tutorial/




namespace OhDeerEngine
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager() override;

		void Initialize();

		//utility for gamepad
		XINPUT_STATE GetState()const;
		int GetIndex()const;
		bool Connected();

		//thumbstick functions
		glm::vec2 LeftStick()const;
		glm::vec2 RightStick()const;
		bool LStick_InDeadZone()const;
		bool RStick_InDeadZone()const;
		//trigger functions
		float LeftTrigger()const;
		float RightTrigger()const;

		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsPressed(int button) const;

	private:
		friend class Singleton<InputManager>;
		InputManager() = default;

		//std::map<int, InputAction> m_InputActions{};
		XINPUT_STATE m_CurrentState{};
		int m_GamepadIndex{0};
		bool m_GamepadIsConnected{false};

		static BYTE* m_pCurrKeyboardState, * m_pOldKeyboardState;



	};

}
