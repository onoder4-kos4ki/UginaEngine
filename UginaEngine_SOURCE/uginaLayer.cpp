#include "uginaLayer.h"
namespace ugina
{
	Layer::Layer() : mGameObjects{}
	{

	}
	Layer::~Layer()
	{
		for (GameObject*& gameobj : mGameObjects)
		{
			if (gameobj == nullptr)
			{
				continue;
			}
			delete gameobj;
			gameobj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			GameObject::eState state = gameObj->GetActive();
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead)
			{
				continue;
			}
			gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			GameObject::eState state = gameObj->GetActive();
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead)
			{
				continue;
			}
			gameObj->LateUpdate();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			GameObject::eState state = gameObj->GetActive();
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead)
			{
				continue;
			}
			gameObj->Render(hdc);
		}
	}
	void Layer::Destroy()
	{

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			;iter != mGameObjects.end()
			;)
		{
			//현재 게임오브젝트의 상태
			GameObject::eState active = (*iter)->GetActive();
			if (active == GameObject::eState::Dead)
			{
				//이터레이터는 특정요소를 가리키는것 이터레이터에 *를 붙이면 내부데이터 확인가능
				GameObject* deathObj = (*iter);
				//여기서의 iter는 erase함수를 사용한뒤에 삭제된만큼 
				//요쇼들이 그만큼 앞으로 땡겨지기 때문에 iter는 위치상으로는 변하지 않지만
				//가리키는것은 다음요소를 가리키게 된다
				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;
				//그렇기 때문에 iter++을 실행하면 다음요소하나를 건너뛰게 된다. 그러므로 스킵
				continue;
			}

			iter++;
			
		}
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			
		}
		
	}
	void Layer::AddGameObject(GameObject* gameObject)
	{

		if (gameObject == nullptr)
		{
			return;
		}
		mGameObjects.push_back(gameObject);
	}
}