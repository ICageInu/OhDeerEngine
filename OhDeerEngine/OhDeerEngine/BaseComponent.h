#pragma once
#include "pch.h"
namespace OhDeer
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() {};

		//virtual void justaTest() = 0;
		virtual void Initialize() = 0;
		virtual void Render(sf::RenderWindow*)const {};
		virtual void SetGameObject(GameObject* parent);
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other)noexcept = delete;

	protected:
		GameObject* m_pParent;
		bool m_IsInitialized;
	};
}