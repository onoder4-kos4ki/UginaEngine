#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResource()
	{
		Resources::Load<graphics::Texture>(L"CAT", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"PLAYER", L"..\\Resources\\Player.bmp");
	}
}