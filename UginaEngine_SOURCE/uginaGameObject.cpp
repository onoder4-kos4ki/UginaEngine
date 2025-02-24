#include "uginaGameObject.h"
#include "uginaInput.h"
#include "uginaTime.h"
#include "uginaTransform.h"
namespace ugina
{
	//유니티에서는 모든 오브젝트가 트랜스폼 컴포넌트를 갖는다.
	GameObject::GameObject() 
	{
		initializeTransform();
	}

	GameObject::~GameObject()
	{
		for (Component* com : mComponets)
		{
			//메모리 해제
			delete com;
			//메모리를 nullptr로 밀기
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