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

		//pivot is standard left bottom
		void AddTexture(Texture2D* texture, const glm::fvec2& pivot = {0, 1}, bool isAnimated = false, bool reverse = false, const int rows = 0, const int columns = 0, const float frameTime = 0.0f, const int drawWidth = 0, const int drawHeight = 0, const glm::fvec2 srcPos = { 0.0f, 0.0f }, const glm::fvec2 srcDim = { 1.0f, 1.0f }, const glm::fvec2 offSet = { 0.0f, 0.0f }, bool mirror = false, float angle = 0.0f);

	private:
		std::vector<TextureAnimation> m_Animations;
	};
}