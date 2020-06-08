#pragma once
#include "pch.h"
class OhDeerEngine
{
public:
	void Initialize();
	void LoadGame()const;
	void CleanUp();
	void Run();
private:
	sf::RenderWindow* m_pWindow;
	sf::Window* m_pDebugWindow;
};

