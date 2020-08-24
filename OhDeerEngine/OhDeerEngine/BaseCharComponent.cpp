#include "OhDeerPCH.h"
#include "BaseCharComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"


OhDeerEngine::BaseCharComponent::BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider, CharType chartype,bool isController) :
	m_PosNextFrame{},
	m_pCollision{ pCollider },
	m_pTexture{ pTexture },
	m_ScoreOnDeath{ 0 },
	m_CharType{ chartype },
	m_KeyUp{},
	m_KeyDown{},
	m_KeyLeft{},
	m_KeyRight{},
	m_KeyActionOne{},
	m_KeyActionTwo{},
	m_KeyActionThree{},
	m_KeyActionFour{},
	m_ButtonA{ nullptr },
	m_ButtonB{ nullptr },
	m_ButtonY{ nullptr },
	m_ButtonX{ nullptr },
	m_IsController{ isController }
{
	m_MovementSpeed = 75;
	pParent->AddComponent(this);
	pParent->AddComponent(pTexture);
	pParent->AddComponent(pCollider);
}
void OhDeerEngine::BaseCharComponent::Update(const float deltaT)
{
	SpecificUpdate(deltaT);
	Move();
}

void OhDeerEngine::BaseCharComponent::Render() const {}

void OhDeerEngine::BaseCharComponent::SetIsControlledWithController(bool isControlled)
{
	m_IsController = isControlled;
}
bool  OhDeerEngine::BaseCharComponent::GetIsConnectedWithController()const
{
	return m_IsController;
}


glm::vec2 OhDeerEngine::BaseCharComponent::GetDirection() const 
{
	return m_Direction;
}
float OhDeerEngine::BaseCharComponent::GetMovementSpeed() const
{
	return m_MovementSpeed;
}

void OhDeerEngine::BaseCharComponent::FixedUpdate(const float) {}

int OhDeerEngine::BaseCharComponent::GetScoreToAdd() const
{
	return m_ScoreOnDeath;
}

int OhDeerEngine::BaseCharComponent::GetCharacterType() const
{
	return m_CharType;
}

void OhDeerEngine::BaseCharComponent::SetScoreWorth(int score)
{
	m_ScoreOnDeath = score;
}


void OhDeerEngine::BaseCharComponent::Move()
{

	m_pParent->GetTransform()->SetPosition(m_PosNextFrame);

}


void OhDeerEngine::BaseCharComponent::BindActionA(Command* newCommand)
{
	m_ButtonA = newCommand;
}

void OhDeerEngine::BaseCharComponent::BindActionB(Command* newCommand)
{
	m_ButtonB = newCommand;
}

void OhDeerEngine::BaseCharComponent::BindActionY(Command* newCommand)
{
	m_ButtonY = newCommand;
}

void OhDeerEngine::BaseCharComponent::BindActionX(Command* newCommand)
{
	m_ButtonX = newCommand;
}

void OhDeerEngine::BaseCharComponent::SetKeyboardKeys(const SDL_Keycode& up, const SDL_Keycode& down, const SDL_Keycode& left, const SDL_Keycode& right)
{
	m_KeyUp = up;
	m_KeyDown = down;
	m_KeyLeft = left;
	m_KeyRight = right;
}

void OhDeerEngine::BaseCharComponent::SetKeyboardActions(const SDL_Keycode& one, const SDL_Keycode& two, const SDL_Keycode& three, const SDL_Keycode& four)
{
	m_KeyActionOne = one;
	m_KeyActionTwo = two;
	m_KeyActionThree = three;
	m_KeyActionFour = four;
}
