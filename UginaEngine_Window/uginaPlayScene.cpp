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
#include "uginaRenderer.h"
#include "uginaAnimator.h"
#include "uginaCat.h"
#include "uginaCatScript.h"
#include "uginaBoxCollider2D.h"
#include "uginaCircleCollider2D.h"
#include "uginaCollisionManager.h"
#include "uginaTile.h"
#include "uginaTilemapRenderer.h"
#include "uginaRigidbody.h"
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
		FILE* pFile = nullptr;
		_wfopen_s(&pFile,L"..\\Resources\\Test", L"rb");
		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;
			if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) == NULL)
				break;

			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
			TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			tmr->SetIndex(Vector2(idxX, idxY));

		}
		fclose(pFile);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);

		//플레이씬에서 쓰이는 메인카메라 설정
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
		Camera* cameracomp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameracomp;

		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		
		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		//CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();
		collider->SetOffset(Vector2(-50.0f, -50.0));

		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();
		
		playerAnimator->CreateAnimation(L"Idle", playerTex,
			Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
		playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
			, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);

		playerAnimator->PlayAnimation(L"Idle", false);

		playerAnimator->GetCompleteEvent(L"FrontGiveWater") 
			= std::bind(&PlayerScript::AttackEffect, plScript);

		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 250.0f));
		//mPlayer->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));

		mPlayer->AddComponent<Rigidbody>();
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		cat->AddComponent<CatScript>();

		//cameracomp->SetTarget(cat);
		graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		Animator* catAnimator = cat->AddComponent<Animator>();

		//BoxCollider2D* boxCatCollider = cat->AddComponent<BoxCollider2D>();
		CircleCollider2D* circleCatCollider = cat->AddComponent<CircleCollider2D>();
		circleCatCollider->SetOffset(Vector2(-50.f, -50.f));
		//boxCatCollider->SetOffset(Vector2(-50.f, -50.f));
		//catAnimator->CreateAnimation(L"DOWNWALK", catTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"RIGHTWALK", catTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"UPWALK", catTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LEFTWALK", catTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"SITDOWN", catTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"GROOMING", catTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LAYDOWN", catTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		//catAnimator->PlayAnimation(L"SITDOWN", false);
		catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);
		 
		catAnimator->PlayAnimation(L"MushroomIdle", true);

		cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
		cat->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));

		Scene::Initialize();
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
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}