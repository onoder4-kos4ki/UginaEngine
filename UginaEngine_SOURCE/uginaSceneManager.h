#pragma once
#include "uginaScene.h"
namespace ugina
{
	//씬들을 관리해주는 클래스
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			//내부에서 씬을 만들어서 이름을 저장하고, 초기화를 실행해줌 
			T* scene = new T();
			scene->SetName(name);
			scene->Initialize();

			//씬매니저에서 관리하는 mScene 자료구조에 {이름(key),scene(value)}을 한쌍으로 하는 노드를 저장시킴
			mScene.insert(std::make_pair(name, scene));

			//만들어진 씬을 리턴함(참조가 아닌 포인터를 리턴하는 이유는 자료구조에 넣을려고)
			return scene;
		}
		static Scene* LoadScene(const std::wstring& name)
		{
			//name의 키로 저장된 씬을 찾는다
			std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);
			if (iter == mScene.end())
			{
				return nullptr;
			}
			//찾은 씬을 활성화된 씬으로 만든다.
			mActiveScene = iter->second;

			//활성화된 씬을 리턴
			return iter->second;
		}
		


		static void Initialize();
		//현재 선택된 씬(mActiveScene)에서 해야할 로직을 실행시키는 함순
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		//모든 씬을 담는 자료구조 map(트리구조)
		static std::map<std::wstring, Scene*> mScene;
		//씬 매니저에서 현재 활성화 되어있는 씬
		static Scene* mActiveScene;
	};
	
}
