#pragma once
#include "CommonInclude.h"
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


