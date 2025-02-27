#include "uginaPlayScene.h"
#include "uginaGameObject.h"
#include "uginaPlayer.h"
#include "uginaTransform.h"
#include "uginaSpriteRenderer.h"
#include "uginaInput.h"
#include "uginaTitleScene.h"
#include "uginaSceneManager.h"
#include "uginaObject.h"
#include "uginaTexture.h"
#include "uginaResources.h"
#include "uginaPlayerScript.h"
#include "uginaCamera.h"
#include "uginarenderer.h"
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

		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameracomp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameracomp;


		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
		sr->SetSize(Vector2(3.0f, 3.0f));
		mPlayer->AddComponent<PlayerScript>();

		graphics::Texture* packmanTexture = Resources::Find<graphics::Texture>(L"PackMan");
		sr->SetTexture(packmanTexture);

		GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetSize(Vector2(3.0f, 3.0f));
		graphics::Texture* bgTexture= Resources::Find<graphics::Texture>(L"Map");
		
		bgsr->SetTexture(bgTexture);
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		/*if (Input::GetKeyDown(keyCode::A))
		{
			SceneManager::LoadScene(L"TitleScene");
		}*/
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		/*wchar_t str[50] = L"Play Scene";
		TextOut(hdc, 0, 0, str, 10);*/
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		//Transform* tr = bg->GetComponent<Transform>();
		//tr->SetPosition(Vector2(0, 0));
	}
}