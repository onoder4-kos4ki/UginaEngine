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
			//���� ������ �ִϸ��̼��� ����Ϸ�鼭 �����ϴ� �ִϸ��̼��̸�
			//�ִϸ��̼��� �����Լ� ������Ѽ� �ٽ� �����ų �غ��ϱ�
			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
				{
					events->completeEvent();
				}
				//���� ������ �ִϸ��̼��� ����Ϸ�鼭 �����ϴ� �ִϸ��̼��̸�
				//�ִϸ��̼��� �����Լ� ������Ѽ� �ٽ� �����ų �غ��ϱ�
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
		
		//���� �Լ��� �ִϸ��̼��� ����� �Լ��ε� �����̸�����
		//�̹� �������� �ִϸ��̼��� �ִٸ� ����
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
		//���� path�� �������� ������ �̹��� ������ ��ȸ�ؼ� �ε���(������ ���ڴ� �� ��������Ʈ ��Ʈ�� ��)
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
		//�̹��� ������ ũ�⸦ ���� ���ѳ����� �����ϰ�, �̹��� ������ ���� ������ ����ؼ� ��������Ʈ ��Ʈ�� ���� ����
		UINT sheetWidth = images[0]->GetWidth() * fileCount;
		//�̹��� ������ ���̷� ��������Ʈ ��Ʈ�� ���̸� ����
		UINT sheetHeight = images[0]->GetHeight();
		//������ �ܾ�� �̹��������� �̿��ؼ� �ϳ��� ����ִ� ��������Ʈ ��Ʈ ����(���̿� ���� �����Ͽ���)
		graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);

		UINT imageWidth = images[0]->GetWidth();
		UINT imageHeight = images[0]->GetHeight();
		//����ִ� ��������Ʈ ��Ʈ�� images ���;ȿ��ִ� �̹������ ����ִ� ��������Ʈ ��Ʈ�� ä������
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

	//PlayAnimation�� �Ѵٴ°��� ���� �ִϸ��̼��� ������ ���ο� �ִϸ��̼��� �����Ѵٴ¶�
	//(�����ִϸ��̼ǰ� ���� �ִϸ��̼��� �����ϴ���)
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
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}

}
