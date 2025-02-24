#include "uginaPlayScene.h"
#include "uginaGameObject.h"
#include "uginaPlayer.h"
#include "uginaTransform.h"
#include "uginaSpriteRenderer.h"
#include "uginaInput.h"
#include "uginaTitleScene.h"
#include "uginaSceneManager.h"
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
		bg = new Player();
		Transform* tr = bg->AddComponent<Transform>();
		tr->SetPos(Vector2(0, 0));
		tr->SetName(L"TR");
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");
		sr->ImageLoad(L"..\\Resources\\CloudOcean.png");

		AddGameObject(bg,eLayerType::BackGround);
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(keyCode::A))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t str[50] = L"Play Scene";
		TextOut(hdc, 0, 0, str, 10);
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		Transform* tr = bg->GetComponent<Transform>();
		tr->SetPos(Vector2(0, 0));
	}
}