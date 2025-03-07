#include "uginaSpriteRenderer.h"
#include "uginaGameObject.h"
#include "uginaTransform.h"
#include "uginaRenderer.h"
namespace ugina
{
	SpriteRenderer::SpriteRenderer()
		:Component(enums::eComponentType::SpriteRenderer),
		mTexture(nullptr),
		mSize(Vector2::One)//�⺻ ������ 1x1
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{

	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{

		if (mTexture == nullptr)
		{
			assert(false);
		}
		//����Ƽ ����� ������Ʈ�� ��ǥ
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		//������Ʈ�� ���� ��ǥ�� ���Ѱ��� �ƴ� ī�޶� ���� �׷����ϴ� ��ǥ�� ���Ѱ�
		pos = renderer::mainCamera->CalculatePosition(pos);
		//BMP�����϶�
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y,
				mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(),
				RGB(255, 0, 255));
		}
		//png�����϶�
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));

		}
	}



}