#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResource()
	{
		//내부에서 호출할이름은 BG인 배경파일을 로드
		Resources::Load<graphics::Texture>(L"BG",L"..\\Resources\\CloudOcean.png");
	}
}