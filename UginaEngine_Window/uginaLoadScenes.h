#pragma once
#include "..\\UginaEngine_SOURCE\\uginaSceneManager.h"
#include "uginaPlayScene.h"
#include "uginaTitleScene.h"
#include "uginaToolScene.h"
namespace ugina
{
	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		//SceneManager::LoadScene(L"ToolScene");
		SceneManager::LoadScene(L"PlayScene");
		
	}
}