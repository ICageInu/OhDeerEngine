#pragma once
#include "BaseComponent.h"

namespace OhDeerEngine
{
	class TextComponent;
	class Font;
	class FPSComponent :
		public BaseComponent
	{
	public:
		//calling on initialize will do the job for you
		FPSComponent();
		//only call this init after you added fps to a parent
		void Initialize(Font* pFont);
		virtual void Update(const float deltaT) override;
		virtual void Render() const override;
		virtual void FixedUpdate(const float) override;

	private:
		TextComponent* m_Text;
		float m_SecondsTimer{};
		int m_FrameCounter{};
	};

}
