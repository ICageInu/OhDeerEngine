#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
class ServiceLocator
{
public:
	inline static sf::RenderWindow* GetWindow() { return window; }
	inline static void RegisterRenderWindow(sf::RenderWindow* pWindow) { window = pWindow; }

private:
	inline static sf::RenderWindow* window = nullptr;

};