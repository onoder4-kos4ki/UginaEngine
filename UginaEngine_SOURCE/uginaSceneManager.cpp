#include "uginaSceneManager.h"
namespace ugina
{

	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	//�� �Ŵ������� ���� Ȱ��ȭ �Ǿ��ִ� ��
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