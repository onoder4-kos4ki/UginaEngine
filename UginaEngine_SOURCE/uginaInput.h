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
		A,B,C,D,
		E,F,G,H,
		I,J,K,L,
		M,N,O,P,
		Q,R,S,T,
		U,V,W,X,
		Y,Z,
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

		//���ӿ��� Ű�� ���� ���¸� ������������ �Լ���
		
		//���ӿ��� Ű�� ��� �������������� �˱����� �Լ�
		static bool GetKeyDown(keyCode code) { int a = 0;
		return keys[(int)code].state == keyState::Down; }

		//���ӿ��� Ű�� ��� ������������ �˱����� �Լ�
		static bool GetKeyUp(keyCode code) { return keys[(int)code].state == keyState::Up; }

		//���ӿ��� Ű�� �ڴ��������� �˱����� �Լ�
		static bool GetKey(keyCode code) { return keys[(int)code].state == keyState::Pressed; }
	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(Input::Key& key);
		static bool isKeyDown(keyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

		//���� ������ �����ϴ� �迭
		static std::vector<Key> keys;
	};
}

