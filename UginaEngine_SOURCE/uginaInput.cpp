#include "uginaInput.h"



namespace ugina
{
	//����ƽ ������ cpp���Ͽ��� ���� �Ѵ�
	std::vector<Input::Key> Input::keys;


	int ASCII[(UINT)keyCode::Count] = {'W','A','S','D',' '};
	void Input::Update()
	{
		// Keys vector ��ü�� ���鼭 ���ȴ��� �ƴ����� ������
		for (int i = 0; i < keys.size(); i++)
		{
			//���������� Ű�ǻ��¸� ������ ���·� �ܰ������� ��½�Ŵ
			if (GetAsyncKeyState((int)keys[i].code) & 0x8000)
			{
				//������ ���ȴ� ���¶�� �����ܰ�� ������ Pressed
				if (keys[i].bPressed)
				{
					keys[i].state = keyState::Pressed;
				}
				//������ �ȴ��ȴ� ���¶�� �����ܰ�� ������ Down
				else
				{
					keys[i].state = keyState::Down;
				}
				//���� ������Ʈ ���忡�� ����Ű�� ���ȴ� ���´ϱ� �ٲ��ֱ�
				keys[i].bPressed = true;
			}

			//���������� Ű�ǻ��¸� ������ ���·� �ܰ������� ��½�Ŵ
			else
			{
				//������ ���ȴ� ���¶�� �����ܰ�� ������ Up
				if (keys[i].bPressed)
				{
					keys[i].state = keyState::Up;
				}
				//������ �ȴ��ȴ� ���¶�� �����ܰ�� ������ None
				else
				{
					keys[i].state = keyState::None;
				}
				//���� ������Ʈ ���忡�� ����Ű�� �ȴ��ȴ� ���´ϱ� �ٲ��ֱ�
				keys[i].bPressed = false;
			}
		}
	}

	void Input::Initialize()
	{
		//���� ������ Ű�ڵ��� ������ŭ Keys vector�� �⺻������ �ʱ�ȭ ����
		for (int i = 0; i < (int)keyCode::Count; i++)
		{
			//������� Key����ü �ʱ�ȭ
			Key key = {};
			key.bPressed = false;
			key.code = (keyCode)ASCII[i];
			key.state = keyState::None;

			keys.push_back(key);
		}

	}
}

