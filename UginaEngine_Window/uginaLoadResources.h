#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
{
	void LoadResource()
	{
		//���ο��� ȣ�����̸��� BG�� ��������� �ε�
		Resources::Load<graphics::Texture>(L"BG",L"..\\Resources\\CloudOcean.png");
	}
}