#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
	}
}