#include "uginaGameObject.h"
#include "uginaInput.h"
namespace ugina
{

	GameObject::GameObject() 
	{
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

}