#pragma once
#include <glm/common.hpp>
#include <vector>
#include "BaseComponent.h"
namespace OhDeerEngine
{
	class Texture2D;

	struct TextureAnimation
	{
		Texture2D* Image;
		glm::fvec2 Pivot, SrcPos, SrcDim, Offset;
		float FrameTime, CurrTime, Angle;
		int Rows, Columns, CurrFrame, DrawWidth, DrawHeight;
		bool IsAnimated, IsReversed, IsMirrored;
	};

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;
		//~RenderComponent();

		//overrides
		void Update(const float deltaT)override;
		void Render() const override;
		void FixedUpdate(const float deltaT) override;
		void DrawRectangle(const glm::fvec2& pos)const;


		//pivot is standard left bottom
		void SetTexture(Texture2D* texture, const int drawWidth = 0, const int drawHeight = 0, const glm::fvec2& pivot = {0, 1}, bool isAnimated = false, bool reverse = false, const int rows = 0, const int columns = 0, const float frameTime = 0.0f, bool mirror = false, float angle = 0.0f, const glm::fvec2 srcPos = { 0.0f, 0.0f }, const glm::fvec2 srcDim = { 1.0f, 1.0f }, const glm::fvec2 offSet = { 0.0f, 0.0f });

		//pass the width and height of the collision component
		void AddRectangleToDraw(float width, float height);

		TextureAnimation GetTextureAnimation()const;
	private:
		TextureAnimation m_Animation;
		float m_Height, m_Width;
		bool m_DrawRectangle;
	};
}