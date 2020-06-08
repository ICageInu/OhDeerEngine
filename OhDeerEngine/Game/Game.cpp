// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "pch.h"
#include "vld.h"
#include "OhDeerEngine.h"
#include "MainGame.h"

int main(int, char* []) {
	//call maingame before engine, maingame is init
	OhDeerEngine engine;
	engine.Initialize();

	MainGame* pNewGame = new MainGame();
	engine.Run();

	//SafeDelete(pNewGame);
	delete pNewGame;
	pNewGame = nullptr;
	return 0;
}
