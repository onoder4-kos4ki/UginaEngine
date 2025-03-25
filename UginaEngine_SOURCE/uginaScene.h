#pragma once
#include "uginaEntity.h"
#include "uginaGameObject.h"
#include "uginaLayer.h"
namespace ugina
{

	//������ ���
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const enums::eLayerType type);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(int)type]; }
	private: 
		void createLayers();

	private:
		//������ ��� ���ӿ�����Ʈ�� ���̾��� ��ū �з��� ����Ǿ� ������ ����.
		std::vector<Layer*> mLayers;
	};

}

