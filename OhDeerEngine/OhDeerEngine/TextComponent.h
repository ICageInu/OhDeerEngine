#pragma once
#include "BaseComponent.h"
namespace OhDeer
{

	class TextComponent :
		public BaseComponent
	{
	public:
		TextComponent();
		TextComponent(const std::string& assetFileFont);
		TextComponent(const std::string& string, const std::string& assetFileFont);
		virtual ~TextComponent()override;

		virtual void Update(float)override;
		virtual void Initialize()override;
		virtual void Render(sf::RenderWindow*)const override;

		//setters
		void SetFont(const std::string& assetFile);
		void SetFont(sf::Font* font);
		void SetText(const std::string& text);

	private:
		sf::Font* m_pFont;
		sf::Text* m_pString;
	};
}