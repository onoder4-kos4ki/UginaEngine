#include "uginaInput.h"



namespace ugina
{
	//스태틱 변수는 cpp파일에서 정의 한다
	std::vector<Input::Key> Input::keys;


	int ASCII[(UINT)keyCode::Count] = { 'W','A','S','D',' ' };

	void Input::Update()
	{
		updateKeys();
	}

	void Input::Initialize()
	{
		createKeys();
	}
	void Input::createKeys()
	{
		//내가 설정한 키코드의 갯수만큼 Keys vector를 기본값으로 초기화 해줌
		for (int i = 0; i < (int)keyCode::Count; i++)
		{
			//명시적인 Key구조체 초기화
			Key key = {};
			key.bPressed = false;
			key.code = (keyCode)ASCII[i];
			key.state = keyState::None;

			keys.push_back(key);
		}
	}
	void Input::updateKeys()
	{
		
		// Keys vector 전체를 돌면서 눌렸는지 아닌지를 판정함
		std::for_each(keys.begin(), keys.end(), [](Input::Key& key)->void { updateKey(key); });
	}
	void Input::updateKey(Input::Key& key)
	{
		//눌렸을때는 키의상태를 눌리는 상태로 단계적으로 상승시킴
		if (isKeyDown(key.code))
		{
			updateKeyDown(key);
		}
		//때졌을때는 키의상태를 때지는 상태로 단계적으로 상승시킴
		else
		{
			updateKeyUp(key);
		}
	}
	bool Input::isKeyDown(keyCode code)
	{
		return GetAsyncKeyState((int)code & 0x8000);
	}


	void Input::updateKeyDown(Input::Key& key)
	{
		//이전에 눌렸던 상태라면 다음단계는 무조건 Pressed
		if (key.bPressed == true)
		{
			key.state = keyState::Pressed;
		}
		//이전에 안눌렸던 상태라면 다음단계는 무조건 Down
		else
		{
			key.state = keyState::Down;
		}
		//다음 업데이트 입장에선 현재키는 눌렸던 상태니까 바꿔주기
		key.bPressed = true;
	}
	void Input::updateKeyUp(Input::Key& key)
	{
		//이전에 눌렸던 상태라면 다음단계는 무조건 Up
		if (key.bPressed == true)
		{
			key.state = keyState::Up;
		}
		//이전에 안눌렸던 상태라면 다음단계는 무조건 None
		else
		{
			key.state = keyState::None;
		}
		//다음 업데이트 입장에선 현재키는 안눌렸던 상태니까 바꿔주기
		key.bPressed = false;
	}
}

