#pragma once
#include "pch.h"
#include <functional>
namespace OhDeer
{
	class GameObject;


	enum ButtonState 
	{
		PRESSED = 0,
		DOWN,
		RELEASED
	};




	//I command thee to work
	struct Command
	{
		//TODO
		//this struct needs to have a button state
		//and needs to have an empty std function that later on I can tell what to do
		std::function<void()> command;
		//I give it the buttonstate that I want the command to be triggered in, so now I need to figure out how to check if these are correct
		//tl;dr make sure that the buttonstate at present time is same as buttonstate of command
		ButtonState buttonState;
	};




	class InputManager
	{
	public:
		InputManager() = default;
		~InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) noexcept = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) noexcept = delete;

		bool AddInputAction(Command action);
		bool IsActionTriggered(int actionID);
		sf::Vector2<int> GetMousePosition();
	private:
		std::map<int, Command> m_InputActions;
		sf::Vector2<int> m_CurMousePos;
	};



}