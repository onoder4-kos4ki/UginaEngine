#include "uginaAnimator.h"
#include "uginaResources.h"
#include "uginaTexture.h"
namespace ugina
{

	ugina::Animator::Animator()
		:Component(enums::eComponentType::Animator)
		,mAnimations{}
		,mActiveAnimation(nullptr)
		,mbLoop(false)
	{
	}

	ugina::Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void ugina::Animator::Initialize()
	{
	}

	void ugina::Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->GetName());
			//현재 선택한 애니메이션이 재생완료면서 루프하는 애니메이션이면
			//애니메이션의 리셋함수 실행시켜서 다시 재생시킬 준비하기
			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
				{
					events->completeEvent();
				}
				//현재 선택한 애니메이션이 재생완료면서 루프하는 애니메이션이면
				//애니메이션의 리셋함수 실행시켜서 다시 재생시킬 준비하기
				if (mbLoop == true)
				{
					mActiveAnimation->Reset();
				}
				
			}
		}
	}

	void ugina::Animator::LateUpdate()
	{
	}

	void ugina::Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void ugina::Animator::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		
		//현재 함수는 애니메이션을 만드는 함수인데 현재이름으로
		//이미 만들어놓은 애니메이션이 있다면 리턴
		if (animation != nullptr)
		{
			return;
		}
		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);
		animation->SetAnimator(this);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name,events));
		mAnimations.insert(std::make_pair(name, animation));
		//TODO
	}

	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
	{


		Animation* animation = nullptr;
		animation = FindAnimation(name);
		
		if (animation!= nullptr)
		{
			return;
		}

		int fileCount = 0;
		//현재 path를 기준으로 하위의 이미지 파일을 순회해서 로드함(파일의 숫자는 곧 스프라이트 시트의 폭)
		std::filesystem::path fs(path);
		std::vector<graphics::Texture*> images = {};
		for (auto& p : std::filesystem::recursive_directory_iterator(fs))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);
			images.push_back(texture);
			fileCount++;
		}
		//이미지 파일의 크기를 통일 시켜놓은걸 가정하고, 이미지 파일의 폭과 갯수를 사용해서 스프라이트 시트의 폭을 설정
		UINT sheetWidth = images[0]->GetWidth() * fileCount;
		//이미지 파일의 높이로 스프라이트 시트의 높이를 설정
		UINT sheetHeight = images[0]->GetHeight();
		//위에서 긁어온 이미지파일을 이용해서 하나의 비어있는 스프라이트 시트 생성(높이와 폭을 지정하여서)
		graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);

		UINT imageWidth = images[0]->GetWidth();
		UINT imageHeight = images[0]->GetHeight();
		//비어있는 스프라이트 시트에 images 벡터안에있는 이미지들로 비어있는 스프라이트 시트를 채워넣음
		for (size_t i = 0; i < images.size(); i++)
		{
			BitBlt(spriteSheet->GetHdc(), i * imageWidth, 0, imageWidth, imageHeight,
				images[i]->GetHdc(), 0, 0, SRCCOPY);
		}
		CreateAnimation(name, spriteSheet, Vector2(0.0f, 0.0f), Vector2(imageWidth, imageHeight)
			, offset, fileCount, duration);
	}

	ugina::Animation* ugina::Animator::FindAnimation(const std::wstring& name)
	{
		//TODO
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	//PlayAnimation을 한다는것은 이전 애니메이션은 끝났고 새로운 애니메이션을 실행한다는뜻
	//(이전애니메이션과 같은 애니메이션을 실행하더라도)
	void ugina::Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			return;
		}

		if (mActiveAnimation)
		{
			Events* currentEvents = 
				FindEvents(mActiveAnimation->GetName());

			if (currentEvents)
			{
				currentEvents->endEvent();
			}
		}
		Events* nextEvents = FindEvents(animation->GetName());
		if (nextEvents)
		{
			nextEvents->startEvent();
		}
			
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}

}
