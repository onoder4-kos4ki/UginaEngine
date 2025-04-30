#include "uginaGameObject.h"
#include "uginaInput.h"
#include "uginaTime.h"
#include "uginaTransform.h"

namespace ugina::object
{
	void Destroy(GameObject* gameObject)
	{
		if (gameObject != nullptr)
		{
			gameObject->death();
		}
	}
}
namespace ugina
{
	//����Ƽ������ ��� ������Ʈ�� Ʈ������ ������Ʈ�� ���´�.
	GameObject::GameObject()
		:mState(eState::Active)
		,mLayerType(eLayerType::None)
	{
		//�̸� enum ������ƮŸ���� �ִ�ũ�⸸ŭ ���͸� �÷����Ƽ� ���� �ذ�
		mComponents.resize((UINT)enums::eComponentType::End);
		initializeTransform();
	}

	GameObject::~GameObject()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			//�޸� ����
			delete com;
			//�޸𸮸� nullptr�� �б�
			com = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Render(hdc);
		}
	}

	void GameObject::initializeTransform()
	{
		AddComponent<Transform>();
	}
	

}


