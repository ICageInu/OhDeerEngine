#pragma once
#include "BaseComponent.h"
class TextureComponent : public BaseComponent
{
public:
	TextureComponent();
	TextureComponent(const std::string& assetFile);
	virtual ~TextureComponent();

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) noexcept = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other)noexcept = delete;




	virtual void Initialize()override;
	virtual void Render(sf::RenderWindow* pWindow)const override;
	//SETTERS
	void SetTexture(const std::string& assetFile);

	//GETTERS
	sf::Vector2<float> GetTexturePos()const;
	sf::Sprite* GetTexture()const;
private:
	sf::Sprite* m_pTexture;
};

