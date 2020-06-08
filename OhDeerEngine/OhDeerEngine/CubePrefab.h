#pragma once
#include "GameObject.h"
#include "SFML/Graphics/Color.hpp"
class CubePrefab :
	public GameObject
{
public:
	CubePrefab(float width = 1.f, float height = 1.f,
		sf::Color color = (sf::Color::Red));
	virtual ~CubePrefab() = default;

	CubePrefab(const CubePrefab& other) = delete;
	CubePrefab(CubePrefab&& other)noexcept = delete;
	CubePrefab& operator=(const CubePrefab& other) = delete;
	CubePrefab& operator=(CubePrefab&& other)noexcept = delete;


	virtual void Initialize()override;
	virtual void CleanUpSpecific()override;
	virtual void Render(sf::RenderWindow* pWindow) const override;
	virtual void Update(float deltaT)override;

	virtual void SetSize(const sf::Vector2<float>& pos);
	virtual void SetSize(float xpos,float ypos);
	virtual void SetPosition(const sf::Vector2<float>& pos);
	virtual void SetPosition(float xpos,float ypos);

protected:


private:
	
	float m_Width, m_Height;
	sf::Color m_Color;
	sf::RectangleShape* m_pShape;
};

