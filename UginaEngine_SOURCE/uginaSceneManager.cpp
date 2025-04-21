#include "uginaSceneManager.h"
#include "uginaDontDestroyOnLoad.h"
namespace ugina
{

	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	//�� �Ŵ������� ���� Ȱ��ȭ �Ǿ��ִ� ��
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}
	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
		mDontDestroyOnLoad->Render(hdc);
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
	}
	void SceneManager::Release()
	{
		for (auto& iter: mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene)
		{
			//���� ���� ������ �����ϴ� �Լ�
			mActiveScene->OnExit();
		}
		//name�� Ű�� ����� ���� ã�´�
		std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);
		if (iter == mScene.end())
		{
			return nullptr;
		}
		//ã�� ���� Ȱ��ȭ�� ������ �����.
		mActiveScene = iter->second;

		//��� Ȱ��ȭ�� ���� �����Ҷ� ȣ���� �Լ�����
		mActiveScene->OnEnter();
		//Ȱ��ȭ�� ���� ����
		return iter->second;
	}


}