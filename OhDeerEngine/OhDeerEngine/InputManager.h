#pragma once
#include "OhDeerPCH.h"
#include "Xinput.h"
#include "Singleton.h"
#include "glm/common.hpp"
#include <map>
#include <SDL.h>
#include "Commands.h"
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
		glm::vec2 GetLeftStick(bool squareDir = false)const;
		glm::vec2 GetRightStick(bool squareDir = false)const;
		bool LStick_InDeadZone()const;
		bool RStick_InDeadZone()const;
		//trigger functions
		float LeftTrigger()const;
		float RightTrigger()const;

		bool ProcessInput();
		bool AnyButtonPressed() const;
		bool IsPressed(const ControllerButton& button) const;
		bool IsPressed(const SDL_Keycode& button) const;
		bool IsReleased(const SDL_Keycode& button) const;
		bool IsDown(const SDL_Keycode& button) const;

		std::string GetInputString()const;
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;

		std::map<SDL_Keycode, bool> m_KeyboardCurrent{};
		std::map<SDL_Keycode,bool> m_KeyboardOld{};
		std::map<SDL_Keycode,bool> m_KeyboardTemp{};
		XINPUT_STATE m_CurrentState{};
		std::string m_InputString;
		int m_GamepadIndex{0};
		bool m_GamepadIsConnected{false};

	};

}
