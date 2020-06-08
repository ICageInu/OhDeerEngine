#include "MainGame.h"
#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CubePrefab.h"
#include "TextureComponent.h"
#include "TestScene/TestScene.h"
#include "BaseComponent.h"
MainGame::MainGame()
{
	Initialize();
}

void MainGame::Initialize()
{
	//THIS IS IT HERE MOVING ON
	SceneManager::GetInstance().CreateScene(new TestScene());
}
