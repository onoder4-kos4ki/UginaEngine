#pragma once
#include "uginaEntity.h"
#include "uginaGameObject.h"
#include "uginaLayer.h"
namespace ugina
{

	//게임의 장면
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const eLayerType type);

	private: 
		void CreateLayers();

	private:
		//씬에서 모든 게임오브젝트는 레이어라는 더큰 분류에 저장되어 나뉘어 진다.
		std::vector<Layer*> mLayers;
	};

}

