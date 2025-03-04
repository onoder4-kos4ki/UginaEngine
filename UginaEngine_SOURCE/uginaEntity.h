#pragma once
#include "CommonInclude.h"
using namespace ugina::math;

namespace ugina
{
	//�� �������� ����� �ϴ� ��ҵ鿡 �̸��� �ο��Ͽ� ����� �ϱ⿡ ���� �ϰ� ��
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& getName() { return mName;}

	private:
		std::wstring mName;
	};
}


