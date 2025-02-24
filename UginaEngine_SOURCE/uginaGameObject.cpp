#include "uginaGameObject.h"
#include "uginaInput.h"
#include "uginaTime.h"
#include "uginaTransform.h"
namespace ugina
{
	//����Ƽ������ ��� ������Ʈ�� Ʈ������ ������Ʈ�� ���´�.
	GameObject::GameObject() 
	{
		initializeTransform();
	}

	GameObject::~GameObject()
	{
		for (Component* com : mComponets)
		{
			//�޸� ����
			delete com;
			//�޸𸮸� nullptr�� �б�
			com = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		for (Component* com : mComponets)
		{
			com->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* com : mComponets)
		{
			com->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* com : mComponets)
		{
			com->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* com : mComponets)
		{
			com->Render(hdc);
		}
	}

	void GameObject::initializeTransform()
	{
		AddComponent<Transform>();
	}
}