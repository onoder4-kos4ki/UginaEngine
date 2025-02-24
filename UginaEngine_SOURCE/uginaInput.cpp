#include "uginaInput.h"



namespace ugina
{
	//����ƽ ������ cpp���Ͽ��� ���� �Ѵ�
	std::vector<Input::Key> Input::keys = {};


	int ASCII[(UINT)keyCode::Count] = { 
		'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X',
		'Y', 'Z',' ' };

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
		//���� ������ Ű�ڵ��� ������ŭ Keys vector�� �⺻������ �ʱ�ȭ ����
		for (int i = 0; i < (int)keyCode::Count; i++)
		{
			//������� Key����ü �ʱ�ȭ
			Key key = {};
			key.bPressed = false;
			key.code = (keyCode)i;
			key.state = keyState::None;

			keys.push_back(key);
		}
	}
	void Input::updateKeys()
	{
		
		// Keys vector ��ü�� ���鼭 ���ȴ��� �ƴ����� ������
		std::for_each(keys.begin(), keys.end(), [](Key& key)->void { updateKey(key); });
	}
	void Input::updateKey(Input::Key& key)
	{
		//���������� Ű�ǻ��¸� ������ ���·� �ܰ������� ��½�Ŵ
		if (isKeyDown(key.code))
		{
			updateKeyDown(key);
		}
		//���������� Ű�ǻ��¸� ������ ���·� �ܰ������� ��½�Ŵ
		else
		{
			updateKeyUp(key);
		}
	}
	bool Input::isKeyDown(keyCode code)
	{
		return GetAsyncKeyState(ASCII[(int)code]) & 0x8000;
	}


	void Input::updateKeyDown(Input::Key& key)
	{
		//������ ���ȴ� ���¶�� �����ܰ�� ������ Pressed
		if (key.bPressed == true)
		{
			key.state = keyState::Pressed;
		}
		//������ �ȴ��ȴ� ���¶�� �����ܰ�� ������ Down
		else
		{
			key.state = keyState::Down;
		}
		//���� ������Ʈ ���忡�� ����Ű�� ���ȴ� ���´ϱ� �ٲ��ֱ�
		key.bPressed = true;
	}
	void Input::updateKeyUp(Input::Key& key)
	{
		//������ ���ȴ� ���¶�� �����ܰ�� ������ Up
		if (key.bPressed == true)
		{
			key.state = keyState::Up;
		}
		//������ �ȴ��ȴ� ���¶�� �����ܰ�� ������ None
		else
		{
			key.state = keyState::None;
		}
		//���� ������Ʈ ���忡�� ����Ű�� �ȴ��ȴ� ���´ϱ� �ٲ��ֱ�
		key.bPressed = false;
	}
}

