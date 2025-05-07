#include "uginaInput.h"
#include "uginaApplication.h"

extern ugina::Application api;
namespace ugina
{
	//����ƽ ������ cpp���Ͽ��� ���� �Ѵ�
	std::vector<Input::Key> Input::keys = {};
	//���콺��ǥ�� �ʱ�ȭ 
	math::Vector2 Input::mMousePosition = math::Vector2::One;

	int ASCII[(UINT)ekeyCode::Count] = { 
		'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X',
		'Y', 'Z',' '
		,VK_LBUTTON,VK_MBUTTON,VK_RBUTTON};

	void Input::Initialize()
	{
		createKeys();
	}
	void Input::Update()
	{
		updateKeys();
	}
	void Input::createKeys()
	{
		//���� ������ Ű�ڵ��� ������ŭ Keys vector�� �⺻������ �ʱ�ȭ ����
		for (int i = 0; i < (int)ekeyCode::Count; i++)
		{
			//������� Key����ü �ʱ�ȭ
			Key key = {};
			key.bPressed = false;
			key.code = (ekeyCode)i;
			key.state = keyState::None;

			keys.push_back(key);
		}
	}
	void Input::updateKeys()
	{
		// Keys vector ��ü�� ���鼭 ���ȴ��� �ƴ����� ������
		std::for_each(keys.begin(), keys.end(),
			[](Key& key)->void { updateKey(key); });
	}
	void Input::updateKey(Input::Key& key)
	{

		//���� �� �����찡 ��Ŀ�� �Ǿ��ִٸ� Ű�� ���ȴ��� �ȴ��ȴ��� üũ�Ѵ�
		if (GetFocus())
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
			getMousePositionByWindow();
		}
		//��Ŀ�� �Ǿ����� �ʴٸ�, ��ü Ű���� �� ������ ���� ���·� �����
		else
		{
			clearKeys();
		}
		
	}
	bool Input::isKeyDown(ekeyCode code)
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
	void Input::getMousePositionByWindow()
	{
		//���콺 ��ǥ�� ���� �ӽ� ����(����ü)
		POINT mousePos = {};
		//���� ����͸� �������� �� ���콺��ǥ
		GetCursorPos(&mousePos);
		//����͸� �������� �� ���콺��ǥ�� ���� ���������츦 �������� �ٲ���
		ScreenToClient(api.GetHwnd(),&mousePos);

		//�ӽ� ������ �ִ� ���� ��������� �־��ֱ�
		/*
		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;*/

		UINT width = api.GetWidth();
		UINT height = api.Getheight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if (mousePos.x > 0 && mousePos.x < width)
		{
			mMousePosition.x = mousePos.x;
		}
		if (mousePos.y > 0 && mousePos.y < height)
		{
			mMousePosition.y = mousePos.y;
		}

	}
	void Input::clearKeys()
	{
		for (Key& key : keys)
		{
			//�ƹ�ư ���� ��� ���Ȱų�, �ڴ��� ���¶�� ���� ���� ���·� �ٲ���
			if (key.state == keyState::Down || key.state == keyState::Pressed)
			{
				key.state = keyState::Up;
			}
			//�� �� ���¶�� ���� �ƹ��͵� �ƴ� ���·� �ٲ���
			else if (key.state == keyState::Up)
			{
				key.state = keyState::None;
			}
			// ������ ���ȴ°��� ���� �ȴ��ȴٷ� �ٲ���
			key.bPressed = false;
		}
	}
}

