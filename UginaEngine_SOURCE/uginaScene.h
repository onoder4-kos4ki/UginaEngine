#pragma once
#include "uginaEntity.h"
#include "uginaGameObject.h"
namespace ugina
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObject);

	private:
		//������ ��� ���ӿ�����Ʈ�� ���ͷ� ����ȴ�.
		std::vector<GameObject*> mGameObjects;
	};

}

