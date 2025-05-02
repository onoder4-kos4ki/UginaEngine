#pragma once
#include "uginaEntity.h"
#include "CommonInclude.h"
#include "uginaGameObject.h"
namespace ugina
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		//���� ������Ʈ�� ���ִ� �Լ� ���⿡ �ѹ��� ��Ƽ� ���� ��Ų��.
		

		void AddGameObject(GameObject* gameObject);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }
	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> deleteObjs);
		
		void eraseDeadGameObject();
	private:
		std::vector<GameObject*> mGameObjects;
	};
	//�ʹ� �̸��� �� ����
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}