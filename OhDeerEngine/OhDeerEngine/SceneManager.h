#pragma once
#include "Singleton.h"
#include <iostream>
#include <vector>

namespace OhDeerEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		void AddGameScene(Scene* pScene);


		~SceneManager() override;

		void Update(float deltaT);
		void FixedUpdate(float deltaT);
		void Render();

		Scene* GetActiveScene()const;

		//switching scene functions
		void NextScene();
		void PreviousScene();
	private:
		//this is for us to be unable to call on the constructor
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
		int m_ActiveScene{ 1 };
	};
}
