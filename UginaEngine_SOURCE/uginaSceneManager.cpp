#include "uginaSceneManager.h"
namespace ugina
{

	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	//씬 매니저에서 현재 활성화 되어있는 씬
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initialize()
	{
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
}