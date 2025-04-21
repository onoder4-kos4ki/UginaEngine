#pragma once
#include "CommonInclude.h"

namespace ugina
{
	enum class keyState
	{
		//��� ����
		Down,
		//�� ����
		Pressed,
		//��� ������
		Up,
		None,
		Count
	};
	enum class ekeyCode
	{
		A,B,C,D,
		E,F,G,H,
		I,J,K,L,
		M,N,O,P,
		Q,R,S,T,
		U,V,W,X,
		Y,Z,
		Space,
		LButton,MButton,RButton,
		Count
	};


	class Input
	{
		//���ȴ��� �˻��ϴ� �Լ�
	public:
		struct Key
		{
			//������ ��������
			bool bPressed;
			//Ű�� ����
			keyState state;
			//���� Ű�ڵ�
			ekeyCode code;
		};
		static void Initialize();
		static void Update();
		
		//���� Ű�� �������� ������ ����
		

		//���ӿ��� Ű�� ���� ���¸� ������������ �Լ���
		
		//���ӿ��� Ű�� ��� �������������� �˱����� �Լ�
		__forceinline static bool GetKeyDown(ekeyCode code) { return keys[(int)code].state == keyState::Down; }

		//���ӿ��� Ű�� ��� ������������ �˱����� �Լ�
		__forceinline static bool GetKeyUp(ekeyCode code) { return keys[(int)code].state == keyState::Up; }

		//���ӿ��� Ű�� �ڴ��������� �˱����� �Լ�
		__forceinline static bool GetKey(ekeyCode code) { return keys[(int)code].state == keyState::Pressed; }

		__forceinline static math::Vector2 GetMousePosition() { return mMousePosition; }
	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(Input::Key& key);
		static bool isKeyDown(ekeyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);
		//���� �����츦 �������� �ϴ� ���콺 ��ǩ���� ����
		static void getMousePositionByWindow();
		static void clearKeys();
		//���� ������ �����ϴ� �迭
		static std::vector<Key> keys;
		//���콺 ��ǥ�� ����
		static math::Vector2 mMousePosition;
	};
}

