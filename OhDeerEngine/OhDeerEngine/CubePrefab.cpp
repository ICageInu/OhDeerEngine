#include "CubePrefab.h"
#include "pch.h"
#include "TextureComponent.h"

CubePrefab::CubePrefab(float width, float height, sf::Color color)
	:GameObject()
	, m_Width(width)
	, m_Height(height)
	, m_Color(color)
	, m_pShape(nullptr)

{
	Initialize();
}

void CubePrefab::Initialize()
{
	m_pTransform = new sf::Transform();
	m_pShape = new sf::RectangleShape();
	m_pShape->setSize(sf::Vector2<float>(m_Width, m_Height));

}


void CubePrefab::CleanUpSpecific()
{
	SafeDelete(m_pShape);
}

void CubePrefab::Render(sf::RenderWindow*)const
{
	//auto test = GetComponent<TextureComponent>();

	//if (m_HasTexture) {
	//	//window->draw(*reinterpret_cast<TextureComponent*>();
	//	window->draw(*GetComponent<TextureComponent>()->GetTexture());
	//}
	//else
	//	window->draw(*m_pShape);


}

void CubePrefab::Update([[maybe_unused]] float deltaT)
{
}

void CubePrefab::SetSize(const sf::Vector2<float>& size)
{
	m_Width = size.x;
	m_Height = size.y;
	m_pShape->setSize(size);
	//GetComponent<TextureComponent>()->GetTexture().
}

void CubePrefab::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
	m_pShape->setSize(sf::Vector2<float>(m_Width, m_Height));
}

void CubePrefab::SetPosition(const sf::Vector2<float>& pos)
{
	m_pTransform->translate(pos);
}
void CubePrefab::SetPosition(float xpos, float ypos)
{
	m_pTransform->translate(xpos, ypos);
}
