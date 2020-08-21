#include "OhDeerPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Font.h"
OhDeerEngine::FPSComponent::FPSComponent():
	m_Text{nullptr}
{
}

void OhDeerEngine::FPSComponent::Initialize(Font* pFont)
{
	m_Text = new TextComponent();
	m_Text->AddFont(pFont);
	m_Text->SetText("60");
	m_pParent->GetTransform()->SetPosition({ OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.x/2.0f,0 });
	m_pParent->AddComponent(m_Text);
}


void OhDeerEngine::FPSComponent::Update(const float deltaT)
{
	m_FrameCounter++;
	m_SecondsTimer += deltaT;

	if (m_SecondsTimer >= 1.f)
	{
		m_Text->SetText(std::to_string(m_FrameCounter));
		m_SecondsTimer -= 1.f;
		m_FrameCounter = 0;

	}
}

void OhDeerEngine::FPSComponent::Render() const
{
}

void OhDeerEngine::FPSComponent::FixedUpdate(const float)
{
}
