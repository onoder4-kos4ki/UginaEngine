#pragma once
#include "CommonInclude.h"
namespace ugina
{
	enum keyState
	{
		Down,
		Pressed,
		Up,
		None,
		Count
	};
	enum keyCode
	{
		W,
		A,
		S,
		D,
		Space,
		Count
	};

	struct Key
	{
		//���� ��������
		bool isPressed;
		//Ű�� ����
		keyState state;
		//���� Ű�ڵ�
		keyCode code;
	};
	class uginaInput
	{
		//���ȴ��� �˻��ϴ� �Լ�
	public:
		void Update();
		void Initialize();
		//���� Ű�� �������� ������ ����
	private:

		Key curKey;
		//���� ������ �����ϴ� �迭
		std::vector<Key> Keys;
	};
}

