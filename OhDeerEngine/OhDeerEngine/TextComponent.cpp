#include "pch.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

OhDeer::TextComponent::TextComponent() :
	BaseComponent(),
	m_pFont{ nullptr },
	m_pString{ nullptr }
{}
OhDeer::TextComponent::TextComponent(const std::string& assetFile) :
	BaseComponent(),
	m_pFont{ nullptr },
	m_pString{ nullptr }
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pFont->loadFromFile(assetFile);
}

OhDeer::TextComponent::TextComponent(const std::string& string, const std::string& assetFileFont) :
	BaseComponent(),
	m_pFont{ nullptr },
	m_pString{ nullptr }
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pFont->loadFromFile(assetFileFont);
	m_pString->setFont(*m_pFont);
	m_pString->setString(string);
}

OhDeer::TextComponent::~TextComponent()
{
	SafeDelete(m_pFont);
	SafeDelete(m_pString);

}

void OhDeer::TextComponent::Update(float)
{
	auto posTest = m_pParent->GetTransform()->GetPosition();
	m_pString->setPosition(posTest);
	m_pString->setScale(m_pParent->GetTransform()->GetScale());
}

void OhDeer::TextComponent::Initialize()
{
	m_IsInitialized = true;
	m_pFont = new sf::Font();
	m_pString = new sf::Text();
}

void OhDeer::TextComponent::Render(sf::RenderWindow* pWindow) const
{
	pWindow->draw(*m_pString);
}

void OhDeer::TextComponent::SetFont(const std::string& assetFile)
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pFont->loadFromFile(assetFile);
}

void OhDeer::TextComponent::SetFont(sf::Font* font)
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pFont = font;
}

void OhDeer::TextComponent::SetText(const std::string& text)
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	if (!m_pFont)
	{
		std::string errorLog{ "no font was specified" };
		ImGui::LogText(&(errorLog[0]));
	}
	m_pString->setFont(*m_pFont);
	m_pString->setString(text);
}
