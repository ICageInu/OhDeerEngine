#pragma once
#include "pch.h"
class OhDeerEngine
{
public:
	OhDeerEngine();
	~OhDeerEngine();
	void StartUp();
	void LoadGame()const;
	void CleanUp();
	void Run();
	
protected:
	virtual void Initialize() = 0;
private:
	sf::RenderWindow m_Window;
	sf::Window* m_pDebugWindow;
};

