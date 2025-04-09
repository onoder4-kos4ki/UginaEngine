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

		//���� ������Ʈ�� ���ִ� �Լ� ���⿡ �ѹ��� ��Ƽ� ���� ��Ų��.
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }
	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> deleteObjs);
		void eraseGameObject();

	private:
		std::vector<GameObject*> mGameObjects;
	};
	//�ʹ� �̸��� �� ����
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}