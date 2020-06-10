#pragma once
#include "pch.h"
namespace OhDeer {

	class OhDeerEngine
	{
	public:
		OhDeerEngine();
		~OhDeerEngine() = default;
		void StartUp();
		void LoadGame()const;
		void CleanUp();
		void Run();

	protected:
		virtual void Initialize() = 0;
	private:
		InputManager* m_pInputManager;
		sf::RenderWindow* m_pWindow;
		sf::Window* m_pDebugWindow;
	};

}