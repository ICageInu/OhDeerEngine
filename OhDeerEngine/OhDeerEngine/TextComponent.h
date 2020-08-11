#pragma once
#include "BaseComponent.h"
#include <string>

namespace OhDeerEngine
{
	class Texture2D;
	class Font;
	class TextComponent :
		public BaseComponent
	{
	public:
		TextComponent() = default;
		~TextComponent() override;
		TextComponent(const std::string& text);
		TextComponent(const std::string& text, Font* pFont);
		//overrides
		void Update(const float deltaT)override;
		void Render() const override;
		void FixedUpdate(const float deltaT) override;
		void AddFont(Font* pFont);
		void SetText(const std::string& text);
	private:
		Texture2D* m_pTexture;
		Font* m_pFont;
		std::string m_Text;
		bool m_NeedsUpdate;

	};


}