#include "uginaTitleScene.h"
#include "uginaGameObject.h"
#include "uginaPlayer.h"
#include "uginaTransform.h"
#include "uginaSpriteRenderer.h"

namespace ugina
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		GameObject* tbg = new GameObject();
		Transform* tr=tbg->AddComponent<Transform>();
		tr->SetPos(Vector2(0, 0));
		tr->SetName(L"TTR");
		


		SpriteRenderer* sr =tbg->AddComponent<SpriteRenderer>();
		sr->SetName(L"TSR");
		sr->ImageLoad(L"..\\Resources\\Title2.png");
		AddGameObject(tbg);
		
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}