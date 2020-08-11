#include "OhDeerPCH.h"
#include <SDL.h>
#include <glm/gtx/rotate_vector.hpp>
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "Renderer.h"

void OhDeerEngine::RenderComponent::Update(const float){}

void OhDeerEngine::RenderComponent::Render() const
{
	for (const TextureAnimation& anim : m_Animations)
	{
		const glm::fvec2& pos = m_pParent->GetComponent<TransformComponent>()->GetPosition();

		SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) };
		SDL_QueryTexture(anim.Image->GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);

		//recalculating of dimensions
		//also recalculation of what needed for each curr frame
		SDL_Rect srcRect = { int(anim.SrcPos.x * dstRect.w), int(anim.SrcPos.y * dstRect.h), int(anim.SrcDim.x * dstRect.w), int(anim.SrcDim.y * dstRect.h) };
		if (anim.IsAnimated)
		{
			srcRect = { srcRect.x + (anim.CurrFrame % anim.Columns) * srcRect.w / (anim.Columns),
				srcRect.y + (anim.CurrFrame / anim.Columns) * srcRect.h / (anim.Rows),
				srcRect.w / anim.Columns,
				srcRect.h / anim.Rows };
		}
		if (anim.DrawWidth != 0 && anim.DrawHeight != 0)
		{
			dstRect.w = anim.DrawWidth;
			dstRect.h = anim.DrawHeight;
		}
		SDL_Point pivot = { int(anim.Pivot.x * dstRect.w), int(anim.Pivot.y * dstRect.h) };
		glm::fvec2 worldOffset = { anim.Offset.x * dstRect.w, anim.Offset.y * dstRect.h };
		worldOffset = glm::rotate(worldOffset, -m_pParent->GetComponent<TransformComponent>()->GetRotation() * float(M_PI) / 180.0f);
		dstRect.x += int(worldOffset.x) - pivot.x;
		dstRect.y += int(worldOffset.y) + pivot.y;

		Renderer::GetInstance().RenderTexture(*anim.Image, &dstRect, &srcRect, pivot,m_pParent->GetComponent<TransformComponent>()->GetRotation() + anim.Angle,anim.IsMirrored);
	}
}

void OhDeerEngine::RenderComponent::FixedUpdate(const float deltaT)
{
	for (TextureAnimation& anim : m_Animations) {
		if (!anim.IsAnimated) continue;
		anim.CurrTime += deltaT;
		//this to prevent this from catching up, cause we don't all like sonic
		while (anim.CurrTime >= anim.FrameTime)
		{
			anim.CurrTime -= anim.FrameTime;
			if (anim.IsReversed)
			{
				anim.CurrFrame--;
				if (anim.CurrFrame < 0) anim.CurrFrame += anim.Rows * anim.Columns;
			}
			else {
				anim.CurrFrame++;
				anim.CurrFrame %= anim.Rows * anim.Columns;
			}
		}
	}
}

void OhDeerEngine::RenderComponent::AddTexture(Texture2D* texture, const glm::fvec2& pivot, bool isAnimated, bool reverse, const int rows, const int columns, const float frameTime, const int drawWidth, const int drawHeight, const glm::fvec2 srcPos, const glm::fvec2 srcDim, const glm::fvec2 offSet, bool mirror, float angle)
{
	//TODO please fix naming conventions
	m_Animations.push_back(TextureAnimation{ texture,pivot,srcPos,srcDim,offSet,frameTime,0,angle,rows,columns,0,drawWidth,drawHeight,isAnimated,reverse,mirror });
}
