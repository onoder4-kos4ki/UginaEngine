#pragma once
#include "uginaComponent.h"
#include "uginaGameObject.h"
#include "uginaLayer.h"
#include "uginaScene.h"
#include "uginaSceneManager.h"
#include "uginaTransform.h"

namespace ugina
{
	//오브젝트에 관련한 기능 
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
		static T* Instantiate(ugina::enums::eLayerType type, math::Vector2 positioon)
		{
			T* gameObject = new T();
			Scene* activeScene = SceneManager::Getactivescene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			Transform* tr = gameObject->GetComponent<Transform>();
			tr->SetPosition(positioon);

			return gameObject;
		}
	}
}