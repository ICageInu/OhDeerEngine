#pragma once
#include "Singleton.h"
#include <iostream>
#include <vector>

namespace OhDeerEngine
{
	class Subject;
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		void AddGameScene(Scene* pScene);

		Scene* GetScene(const std::string& name)const;
		Scene* GetScene(size_t index)const;

		~SceneManager() override;

		void Update(float deltaT);
		void FixedUpdate(float deltaT);
		void Render();
		std::vector<Scene*> GetScenes()const;
		Scene* GetActiveScene()const;

		//void SwitchScene(Scene* pScene);
		void SwitchScene(const std::string& sceneName);

		//switching scene functions
		void NextScene();
		void NextScene(Subject* pSubject);
		void NextSceneWithSubject();
		void PreviousScene();
	private:
		//this is for us to be unable to call on the constructor
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
		size_t m_ActiveScene{ 0 };
	};
}
