#include "PickupComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
void PickupComponent::Update(const float deltaT)
{
	if (IsFalling)
		m_pParent->GetTransform()->SetPosition(m_pParent->GetTransform()->GetPosition() + m_FallingDir * deltaT * m_MovingSpeed);
}
