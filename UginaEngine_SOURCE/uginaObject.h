#pragma once
#include "uginaComponent.h"
#include "uginaGameObject.h"
#include "uginaLayer.h"
#include "uginaScene.h"
#include "uginaSceneManager.h"
#include "uginaTransform.h"

namespace ugina
{
	//������Ʈ�� ������ ��� ������ ���� (�� �ܺ� ����ڰ� �����)
	namespace object
	{
		template <typename T>
		static T* Instantiate(ugina::enums::eLayerType type)
		{
			T* gameObject = new T();
			Scene* activeScene = SceneManager::Getactivescene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			return gameObject;
		}
		
		template <typename T>
		static T* Instantiate(ugina::enums::eLayerType type, math::Vector2 position)
		{
			T* gameObject = new T();
			Scene* activeScene = SceneManager::Getactivescene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			Transform* tr = gameObject->GetComponent<Transform>();
			tr->SetPosition(position);

			return gameObject;
		}
		
		static void DontDestroyOnLoad(GameObject* gameObject)
		{
			Scene* activeScene = SceneManager::Getactivescene();

			activeScene->EraseGameObject(gameObject);

			Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
			dontDestroyOnLoad->AddGameObject(gameObject, gameObject->GetLayerType());
		}
		
	}
}