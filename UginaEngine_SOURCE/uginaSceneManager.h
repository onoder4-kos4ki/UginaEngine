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
			mActiveScene = scene;
			scene->Initialize();

			//���Ŵ������� �����ϴ� mScene �ڷᱸ���� {�̸�(key),scene(value)}�� �ѽ����� �ϴ� ��带 �����Ŵ
			mScene.insert(std::make_pair(name, scene));

			//������� ���� ������(������ �ƴ� �����͸� �����ϴ� ������ �ڷᱸ���� ��������)
			return scene;
		}
		static Scene* LoadScene(const std::wstring& name);

		static Scene* Getactivescene() { return mActiveScene; }
		static void Initialize();
		//���� ���õ� ��(mActiveScene)���� �ؾ��� ������ �����Ű�� �Լ�
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		//������ �޸𸮸� ���������ִ� �Լ�
		static void Release();

	private:
		//��� ���� ��� �ڷᱸ�� map(Ʈ������)
		static std::map<std::wstring, Scene*> mScene;
		//�� �Ŵ������� ���� Ȱ��ȭ �Ǿ��ִ� ��
		static Scene* mActiveScene;
	};
	
}
