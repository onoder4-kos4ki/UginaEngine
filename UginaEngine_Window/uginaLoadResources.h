#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResource()
	{
		//���ο��� ȣ�����̸��� BG�� ��������� �ε�
		Resources::Load<graphics::Texture>(L"BG",L"..\\Resources\\CloudOcean.png");
		
		Resources::Load<graphics::Texture>(L"MAP", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PACKMAN", L"..\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>(L"CAT", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"BUBBLE", L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>(L"MAPLEEFFECT", L"..\\Resources\\ezgif.com-gif-maker.png");
		Resources::Load<graphics::Texture>(L"PLAYER", L"..\\Resources\\Player.bmp");
	}
}