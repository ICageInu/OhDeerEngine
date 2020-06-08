#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "BaseComponent.h"
class RenderComponent;
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Render(sf::RenderWindow* pWindow)const;
	virtual void Update(float deltaT) = 0;
	virtual void CleanUp();

	//SETTERS
	void AddComponent(BaseComponent* pComp);
	void SetHasTexture(bool hasTexture);
	//GETTERS
	sf::Transform* GetTransform()const;
	template<class T>
	T* GetComponent()const;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other)noexcept = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other)noexcept = delete;

protected:

	virtual void Initialize() = 0;
	virtual void CleanUpSpecific() = 0;


	//RenderComponent* m_pRenderComponent;
	bool m_HasTexture;
	sf::Transform* m_pTransform;
	std::vector<BaseComponent*> m_pComponents;
};

//thanks overlord engine
template<class T>
inline T* GameObject::GetComponent() const
{
	const type_info& ti = typeid(T);
	for (auto* component : m_pComponents)
	{
		if (component && typeid(*component) == ti)
			return reinterpret_cast<T*>(component);
	}
	return nullptr;
}
