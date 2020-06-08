// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "pch.h"
#include "vld.h"
#include "OhDeerEngine.h"
#include "MainGame.h"

int main(int, char* []) {
	////call maingame before engine, maingame is init
	//MainGame engine;
	//engine.StartUp();

	MainGame* pNewGame = new MainGame();
	pNewGame->StartUp();
	pNewGame->Run();

	//SafeDelete(pNewGame);
	delete pNewGame;
	pNewGame = nullptr;
	return 0;
}
