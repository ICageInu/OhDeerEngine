#include "TextureComponent.h"
#include "ResourceManager.h"

using namespace OhDeer;
TextureComponent::TextureComponent()
	:BaseComponent()
	, m_pSprite(nullptr)
	//m_pTexture{nullptr}
{}

TextureComponent::TextureComponent(const std::string& assetFile) :
	BaseComponent()
{
	//m_IsInitialized = true;

	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetFile);

	m_pSprite->setTexture(*m_pTexture);
}

TextureComponent::TextureComponent(sf::Texture* pTex) :
	BaseComponent()
{
	if (!m_IsInitialized)
	{
		Initialize();
	}
	m_pTexture = pTex;

	m_pSprite->setTexture(*pTex);
}


TextureComponent::~TextureComponent()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

void TextureComponent::Initialize()
{
	m_IsInitialized = true;
	//m_pTexture = new sf::Texture();
	m_pSprite = new sf::Sprite();
}

void TextureComponent::Render(sf::RenderWindow* pWindow) const
{
	pWindow->draw(*m_pSprite);
	//ServiceLocator::GetWindow()->draw(*m_pTexture);
}

void TextureComponent::SetTexture(const std::string& assetFile)
{
	if (!m_IsInitialized)
	{
		Initialize();
	}

	m_pTexture = ResourceManager::GetInstance().LoadTexture(assetFile);

	m_pSprite->setTexture(*m_pTexture);
}

sf::Vector2<float> TextureComponent::GetTexturePos() const
{
	return m_pSprite->getPosition();
}

sf::Sprite* TextureComponent::GetTexture() const
{
	return m_pSprite;
}