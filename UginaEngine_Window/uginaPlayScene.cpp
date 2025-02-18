#include "uginaPlayScene.h"
#include "uginaGameObject.h"
#include "uginaPlayer.h"
#include "uginaTransform.h"
#include "uginaSpriteRenderer.h"
namespace ugina
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			Player* bg = new Player();
			Transform* tr = bg->AddComponent<Transform>();
			tr->SetPos(Vector2(0, 0));
			tr->SetName(L"BTransform");

			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			sr->SetName(L"BSpriteRenderer");
			sr->ImageLoad(L"..\\Resources\\CloudOcean.png");
			AddGameObject(bg);
		}
		
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}