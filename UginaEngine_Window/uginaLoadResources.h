#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResource()
	{
		//���ο��� ȣ�����̸��� BG�� ��������� �ε�
		Resources::Load<graphics::Texture>(L"BG",L"..\\Resources\\CloudOcean.png");
		
		Resources::Load<graphics::Texture>(L"Map", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PackMan", L"..\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
	}
}