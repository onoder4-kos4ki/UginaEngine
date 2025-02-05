#pragma once
#include "CommonInclude.h"

namespace ugina
{
	enum class keyState
	{
		Down,
		Pressed,
		Up,
		None,
		Count
	};
	enum class keyCode
	{
		W,
		A,
		S,
		D,
		Space,
		Count
	};


	class Input
	{
		//���ȴ��� �˻��ϴ� �Լ�
	public:
		static void Update();
		static void Initialize();
		//���� Ű�� �������� ������ ����
		struct Key
		{
			//������ ��������
			bool bPressed;
			//Ű�� ����
			keyState state;
			//���� Ű�ڵ�
			keyCode code;
		};

		//���ӿ��� Ű�� ���� ���¸� ������������ �Լ�
		static bool getKeyDown(keyCode code) { return keys[(int)code].state == keyState::Down; }
		static bool getKeyUp(keyCode code) { return keys[(int)code].state == keyState::Up; }
		static bool getKey(keyCode code) { return keys[(int)code].state == keyState::Pressed; }
	private:


		//���� ������ �����ϴ� �迭
		static std::vector<Key> keys;
	};
}

