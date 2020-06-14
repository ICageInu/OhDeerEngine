#include "TransformComponent.h"
#include "GameObject.h"
using namespace OhDeer;


OhDeer::TransformComponent::TransformComponent() :
	m_Scale{ 1,1 },
	m_OldScale{ 1,1 }
{
	Initialize();
}


OhDeer::TransformComponent::~TransformComponent()
{
	SafeDelete(m_pTransform);
}

void OhDeer::TransformComponent::Initialize()
{
	m_IsInitialized = true;
	m_pTransform = new sf::Transform();
}

void OhDeer::TransformComponent::Update([[maybe_unused]] float deltaT)
{
	if (!m_TransformIsChanged) return;

	//so first inverse everything TRS - SRT

	m_pTransform->scale(1.f / m_OldScale.x, 1.f / m_OldScale.y);



	//TRS
	//FIRST TRANSFORM
	m_pTransform->translate(m_TransformPoint);



	//SCALE
	m_pTransform->scale(m_Scale);


	m_OldScale = m_Scale;

	m_TransformIsChanged = false;
}

void OhDeer::TransformComponent::Translate(float x, float y)
{
	Translate(sf::Vector2f(x, y));
}

//eyo this makes sense smart ass, sfml first translates then it scales, but if you first scale and then translate ofcourse it's gonna mess up
//yeah I cheated this, don't shoot me
void OhDeer::TransformComponent::Translate(const sf::Vector2f& dir)
{
	m_TransformIsChanged = true;
	m_TransformPoint = dir;
}

//these two don't work
//void OhDeer::TransformComponent::SetPosition(float x, float y)
//{
//	SetPosition(sf::Vector2(x, y));
//}
//
//void OhDeer::TransformComponent::SetPosition(const sf::Vector2<float>& newPos)
//{
//	m_Width = newPos.x;
//	m_Height = newPos.y;
//}

void OhDeer::TransformComponent::SetScale(float x, float y)
{
	SetScale(sf::Vector2(x, y));
}

void OhDeer::TransformComponent::SetScale(const sf::Vector2<float>& newSize)
{
	m_TransformIsChanged = true;
	m_Scale = newSize;
}


const sf::Vector2f OhDeer::TransformComponent::GetDimensions() const
{
	return sf::Vector2f(m_Width, m_Height);
}

const sf::Vector2f OhDeer::TransformComponent::GetPosition() const
{
	auto temp = m_pTransform->getMatrix();
	sf::Vector3f pos = sf::Vector3f(temp[12], temp[13], temp[14]);
	return sf::Vector2f(pos.x, pos.y);
}

const sf::Vector2f& OhDeer::TransformComponent::GetScale() const
{
	return m_Scale;
}

const sf::Transform& OhDeer::TransformComponent::GetTransform() const
{
	return *m_pTransform;
}
