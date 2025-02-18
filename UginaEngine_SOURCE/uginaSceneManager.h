#pragma once
#include "uginaScene.h"
namespace ugina
{
	//������ �������ִ� Ŭ����
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			//���ο��� ���� ���� �̸��� �����ϰ�, �ʱ�ȭ�� �������� 
			T* scene = new T();
			scene->SetName(name);
			scene->Initialize();

			//���Ŵ������� �����ϴ� mScene �ڷᱸ���� {�̸�(key),scene(value)}�� �ѽ����� �ϴ� ��带 �����Ŵ
			mScene.insert(std::make_pair(name, scene));

			//������� ���� ������(������ �ƴ� �����͸� �����ϴ� ������ �ڷᱸ���� ��������)
			return scene;
		}
		static Scene* LoadScene(const std::wstring& name)
		{
			//name�� Ű�� ����� ���� ã�´�
			std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);
			if (iter == mScene.end())
			{
				return nullptr;
			}
			//ã�� ���� Ȱ��ȭ�� ������ �����.
			mActiveScene = iter->second;

			//Ȱ��ȭ�� ���� ����
			return iter->second;
		}
		


		static void Initialize();
		//���� ���õ� ��(mActiveScene)���� �ؾ��� ������ �����Ű�� �Լ�
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		//��� ���� ��� �ڷᱸ�� map(Ʈ������)
		static std::map<std::wstring, Scene*> mScene;
		//�� �Ŵ������� ���� Ȱ��ȭ �Ǿ��ִ� ��
		static Scene* mActiveScene;
	};
	
}
