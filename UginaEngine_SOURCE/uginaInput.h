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
		//현재 눌림상태
		bool isPressed;
		//키의 상태
		keyState state;
		//눌린 키코드
		keyCode code;
	};
	class uginaInput
	{
		//눌렸는지 검사하는 함수
	public:
		void Update();
		void Initialize();
		//눌린 키의 종합적인 상태의 변수
	private:

		Key curKey;
		//위의 변수를 저장하는 배열
		std::vector<Key> Keys;
	};
}

