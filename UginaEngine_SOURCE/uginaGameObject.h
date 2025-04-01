#pragma once
#include "CommonInclude.h"
#include "uginaComponent.h"
namespace ugina
{
	namespace object
	{
		void Destroy(GameObject* gameObject);
	}
}
namespace ugina
{

	class GameObject
	{
	public:
		friend void object::Destroy(GameObject* obj);
		enum class eState
		{
			//활성
			Active,
			//감춰짐
			Paused,
			//죽음
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->Initialize();
			component->SetOwner(this);

			//벡터의 값을 푸시 백함수를 쓰는 대신에 enums 타입을 인덱스로 사용
			//mComponets.push_back(comp);
			mComponents[(UINT)component->GetType()] = component;
			return component;
		}
		template <typename T>
		T* GetComponent()
		{

			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				//mComponents안에 있는 컴포넌트들을 하나하나 캐스팅해봄
				component = dynamic_cast<T*>(comp);
				//캐스팅한것이 잘되서 component안에 들어가면 반복문 탈출
				if (component)
				{
					break;
				}
			}
			return component;
		}
		eState GetState() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)
			{
				mState = eState::Active;
			}
			if (power == false)
			{
				mState = eState::Paused;
			}
		}
		void Death() { mState = eState::Dead; }                    
		bool IsActive() { return  mState == eState::Active; }
		bool IsDead() { return mState == eState::Dead; }


	private:
		void initializeTransform();
		void death() { mState = eState::Dead; }
	private:
		eState mState;
		std::vector<Component*> mComponents;

	};
}


