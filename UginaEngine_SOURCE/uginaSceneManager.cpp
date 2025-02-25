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
	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene)
		{
			//현재 씬을 나갈때 실행하는 함수
			mActiveScene->OnExit();
		}
		//name의 키로 저장된 씬을 찾는다
		std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);
		if (iter == mScene.end())
		{
			return nullptr;
		}
		//찾은 씬을 활성화된 씬으로 만든다.
		mActiveScene = iter->second;

		//방금 활성화된 씬을 시작할때 호출할 함수실행
		mActiveScene->OnEnter();
		//활성화된 씬을 리턴
		return iter->second;
	}


}