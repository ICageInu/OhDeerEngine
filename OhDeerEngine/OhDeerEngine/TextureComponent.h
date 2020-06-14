#pragma once
#include "BaseComponent.h"
namespace OhDeer
{

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent();
		TextureComponent(sf::Texture* pTex);
		TextureComponent(const std::string& assetFile);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other)noexcept = delete;

		virtual void Update(float deltaT) override;
		virtual void Initialize()override;
		virtual void Render(sf::RenderWindow* pWindow)const override;
		//SETTERS
		void SetTexture(const std::string& assetFile);

		//GETTERS
		//sf::Vector2<float> GetTexturePos()const;
		sf::Sprite* GetTexture()const;
	private:
		sf::Sprite* m_pSprite;
		sf::Texture* m_pTexture;
	};


}