#pragma once
#include "..\\UginaEngine_SOURCE\\uginaSceneManager.h"
#include "uginaPlayScene.h"
#include "uginaTitleScene.h"
namespace ugina
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");


		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"TitleScene");
	}
}