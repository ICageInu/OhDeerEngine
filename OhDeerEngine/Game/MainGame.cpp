#include "MainGame.h"
#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TestScene/TestScene.h"
#include "BaseComponent.h"
MainGame::MainGame():
	OhDeerEngine()
{}

void MainGame::Initialize()
{
	//THIS IS IT HERE MOVING ON
	OhDeer::SceneManager::GetInstance().CreateScene(new TestScene());
}
