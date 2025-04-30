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
	//유니티에서는 모든 오브젝트가 트랜스폼 컴포넌트를 갖는다.
	GameObject::GameObject()
		:mState(eState::Active)
		,mLayerType(eLayerType::None)
	{
		//미리 enum 컴포넌트타입의 최대크기만큼 벡터를 늘려놓아서 오류 해결
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
			//메모리 해제
			delete com;
			//메모리를 nullptr로 밀기
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


