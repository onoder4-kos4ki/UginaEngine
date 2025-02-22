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
		//눌렸는지 검사하는 함수
	public:
		static void Update();
		static void Initialize();
		//눌린 키의 종합적인 상태의 변수
		struct Key
		{
			//이전에 눌림상태
			bool bPressed;
			//키의 상태
			keyState state;
			//눌린 키코드
			keyCode code;
		};

		//게임에서 키가 눌린 상태를 기져오기위한 함수
		static bool GetKeyDown(keyCode code) { return keys[(int)code].state == keyState::Down; }
		static bool GetKeyUp(keyCode code) { return keys[(int)code].state == keyState::Up; }
		static bool GetKey(keyCode code) { return keys[(int)code].state == keyState::Pressed; }
	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(Input::Key& key);
		static bool isKeyDown(keyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

		//위의 변수를 저장하는 배열
		static std::vector<Key> keys;
	};
}

