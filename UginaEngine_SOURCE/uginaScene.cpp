#include "uginaScene.h"
namespace ugina
{

	Scene::Scene() : mLayers{}
	{
		createLayers();
	}

	Scene::~Scene()
	{
		for (Layer*& layer : mLayers)
		{
			delete layer;
			layer = nullptr;
		}
	}

	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->Render(hdc);
		}
	}
	void Scene::Destroy()
	{
		//씬에는 레이어벡터가 있고 레이어벡터안에는 레이어가 있고
		//레이어 아래는 오브젝트벡터가 있고 오브젝트 벡터아래는 오브젝트가 존재
		for (Layer* layer : mLayers) 
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->Destroy();
		}
	}
	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* gameObj, const enums::eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(gameObj);
	}
	void Scene::createLayers()
	{
		mLayers.resize((UINT)enums::eLayerType::Max);
		for (size_t i = 0; i < (UINT)enums::eLayerType::Max; i++)
		{
			mLayers[i] = new Layer();
		}
	}
}