#include "uginaLayer.h"
#include "uginaGameObject.h"
namespace ugina
{
	Layer::Layer() : mGameObjects{}
	{

	}
	Layer::~Layer()
	{
		for (GameObject* gameobj : mGameObjects)
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
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
			if (gameObj->IsActive()==false)
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
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
			if (gameObj->IsActive() == false)
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
			
			//���� ���ӿ�����Ʈ�� ���°� ���� Ȥ�� ���� ���¸� ��ŵ
			if (gameObj->IsActive() == false)
			{
				continue;
			}
			gameObj->Render(hdc);
		}
	}
	void Layer::Destroy()
	{
	#pragma region ���Ž�
		//for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
		//	; iter != mGameObjects.end()
		//	;)
		//{
		//	//���� ���ӿ�����Ʈ�� ����
		//	GameObject::eState active = (*iter)->GetState();
		//	if (active == GameObject::eState::Dead)
		//	{
		//		//���ͷ����ʹ� Ư����Ҹ� ����Ű�°� ���ͷ����Ϳ� *�� ���̸� ���ε����� Ȯ�ΰ���
		//		GameObject* deathObj = (*iter);
		//		//���⼭�� iter�� erase�Լ��� ����ѵڿ� �����ȸ�ŭ 
		//		//������ �׸�ŭ ������ �������� ������ iter�� ��ġ�����δ� ������ ������
		//		//����Ű�°��� ������Ҹ� ����Ű�� �ȴ�
		//		iter = mGameObjects.erase(iter);

		//		delete deathObj;
		//		deathObj = nullptr;
		//		//�׷��� ������ iter++�� �����ϸ� ��������ϳ��� �ǳʶٰ� �ȴ�. �׷��Ƿ� ��ŵ
		//		continue;
		//	}

		//	iter++;

		//}
		//for (GameObject* gameObj : mGameObjects)
		//{
		//	if (gameObj == nullptr)
		//	{
		//		continue;
		//	}

		//}

#pragma endregion
		std::vector<GameObject*> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		eraseDeadGameObject();
		deleteGameObjects(deleteObjects);
	}
	void Layer::AddGameObject(GameObject* gameObject)
	{

		if (gameObject == nullptr)
		{
			return;
		}
		mGameObjects.push_back(gameObject);
	}
	void Layer::EraseGameObject(GameObject* eraseGameObj)
	{
		std::erase_if(mGameObjects, [=](GameObject* gameobj)
			{
				return gameobj == eraseGameObj; 
			});
	}
	void Layer::findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs)
	{
		//gameObjs�� ������ ���ӿ�����Ʈ���� �����͸� ��� �ӽð���
		for (GameObject* gameObj : mGameObjects)
		{
			GameObject::eState active = gameObj->GetState();
			if (active == GameObject::eState::Dead)
			{
				gameObjs.push_back(gameObj);
			}
		}
	}
	void Layer::deleteGameObjects(std::vector<GameObject*> deleteObjs)
	{
		for (GameObject* obj : deleteObjs)
		{
			delete obj;
			obj = nullptr;
		}
		
	}
	
	void Layer::eraseDeadGameObject()
	{
		std::erase_if(mGameObjects, [](GameObject* gameObj) 
			{
				return gameObj->IsDead(); 
			});
	}
}