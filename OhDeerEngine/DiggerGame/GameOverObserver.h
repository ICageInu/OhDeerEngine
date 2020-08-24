#pragma once
#include "Observer.h"
#include <string>
#include "HighscoreParser.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputComponent.h"
#include "Subject.h"
#include "ScoreObserver.h"
#include "Factory.h"
#include "InputManager.h"
class GameOverObserver : public OhDeerEngine::Observer
{
public:
	GameOverObserver() = default;
	virtual ~GameOverObserver() {};
	GameOverObserver(const GameOverObserver& other) = delete;
	GameOverObserver(GameOverObserver&& other) = delete;
	GameOverObserver& operator=(const GameOverObserver& other) = delete;
	GameOverObserver& operator=(GameOverObserver&& other) = delete;
	virtual void OnNotify(const char eventType = 0) override
	{
		switch (eventType)
		{
		case 'L':

			Highscore highscore;
			std::string inits{};
			int score{};
			auto objs = OhDeerEngine::SceneManager::GetInstance().GetScene("0")->GetObjects();
			auto observers = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->Observers;
			for (size_t i = 0; i < objs.size(); i++)
			{
				auto inputComp = objs[i]->GetComponent<InputComponent>();
				if (inputComp)
				{
					inits = inputComp->GetInitials();
					break;
				}
			}

			for (size_t i = 0; i < observers.size(); i++)
			{
				if (typeid(*observers[i]) == typeid(ScoreObserver))
				{
					score = static_cast<ScoreObserver*>(observers[i])->GetScore();
					break;
				}

			}

			highscore.SaveHighscore("./Resources/highscores.txt",score,inits);
			OhDeerEngine::InputManager::GetInstance().SetCloseWindow(true);
			break;
		}
	};
};