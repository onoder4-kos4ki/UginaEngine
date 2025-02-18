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
		//씬에서 모든 게임오브젝트는 벡터로 저장된다.
		std::vector<GameObject*> mGameObjects;
	};

}

