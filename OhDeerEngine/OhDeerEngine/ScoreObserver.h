#pragma once
#include "Observer.h"
namespace OhDeerEngine
{
	class TextComponent;
	class BaseCharComponent;
	class ScoreObserver :
		public Observer
	{
	public:
		ScoreObserver(TextComponent* pScore);
		virtual void OnNotify(const BaseCharComponent& characterComp) override;
		
	private:
		//needs a reference to the score gameobject with a textcomponent telling the player how much score they have
		TextComponent* m_pScore;
		int m_ScoreValue;
	};

}
