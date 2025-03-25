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
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
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
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
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
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
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
			//���� ���ӿ�����Ʈ�� ����
			GameObject::eState active = (*iter)->GetActive();
			if (active == GameObject::eState::Dead)
			{
				//���ͷ����ʹ� Ư����Ҹ� ����Ű�°� ���ͷ����Ϳ� *�� ���̸� ���ε����� Ȯ�ΰ���
				GameObject* deathObj = (*iter);
				//���⼭�� iter�� erase�Լ��� ����ѵڿ� �����ȸ�ŭ 
				//������ �׸�ŭ ������ �������� ������ iter�� ��ġ�����δ� ������ ������
				//����Ű�°��� ������Ҹ� ����Ű�� �ȴ�
				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;
				//�׷��� ������ iter++�� �����ϸ� ��������ϳ��� �ǳʶٰ� �ȴ�. �׷��Ƿ� ��ŵ
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