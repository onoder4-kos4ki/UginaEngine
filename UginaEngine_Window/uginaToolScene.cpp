#include "uginaToolScene.h"
#include "uginaObject.h"
#include "uginaCamera.h"
#include "uginaCameraScript.h"
#include "uginaRenderer.h"
#include "uginaInput.h"
#include "uginaTilemapRenderer.h"
#include "uginaTexture.h"
#include "uginaResources.h"
namespace ugina
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		 
		renderer::mainCamera = cameraComp;

		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
			if (Input::GetKeyDown(ekeyCode::LButton))
			{
				Vector2 pos = Input::GetMousePosition();
				pos = renderer::mainCamera->CalculateTilePosition(pos);
				
				if (pos.x >= 0.0f && pos.y >= 0.0f)
				{
					int idxX = pos.x / TilemapRenderer::TileSize.x;
					int idxY = pos.y / TilemapRenderer::TileSize.y;

					Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
					TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
					tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
					tmr->SetIndex(TilemapRenderer::SelectedIndex);

					tile->SetIndexPosition(idxX, idxY);
					mTiles.push_back(tile);
				}
				else
				{

				}
			}
			if (Input::GetKeyDown(ekeyCode::S))
			{
				Save();
			}
			if (Input::GetKeyDown(ekeyCode::L))
			{
				Load();
			}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 0; i < 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(TilemapRenderer::TileSize.x * i, 0.0f)
			);
			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}
		for (size_t  i= 0;  i< 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition(
				Vector2(0.0f, TilemapRenderer::TileSize.y * i)
			);
			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1000, pos.y);
		}
	}
	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
	void ToolScene::Save()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		//GetSaveFileName 대화상자를 여는 함수 대화상자가 열려있는 순간은 프로그램이 멈춤
		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");
	
		for (Tile * tile : mTiles)
		{
			TilemapRenderer* tmr = tile->GetComponent<TilemapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, pFile);
		}
		fclose(pFile);
	}
	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};
	}
}

LRESULT WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM LParam)
{
	return LRESULT();
}
