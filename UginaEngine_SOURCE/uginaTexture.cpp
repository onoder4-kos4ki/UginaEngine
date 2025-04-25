#include "uginaTexture.h"
#include "uginaApplication.h"
#include "uginaResources.h"
extern ugina::Application api;
namespace ugina
{
	
	namespace graphics
	{
		//��������Ʈ���� ����� �ؽ��� ��� ���ҽ��� �����ϴ� ���ҽ��� �������̵� �Լ�
		Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
		{
			Texture* image = Resources::Find<Texture>(name);

			if (image)
			{
				return image;
			}
			image = new Texture();
			image->SetName(name);
			image->SetWidth(width);
			image->SetHeight(height);

			#pragma region �̹��������� �����ϱ����� �ʼ��۾�
			HDC hdc = api.GetHdc();
			HWND hwnd = api.GetHwnd();
			//���� dc�� ȣȯ�Ǵ� ��Ʈ�ʰ� 
			//��dc�� �� �����쿡�� ����ϴ� ������ dc�͵� ȣȯ�����ؾ���
			image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
			image->mHdc = CreateCompatibleDC(hdc);

			///�ڽ��ݶ��̴��� �׸������� �귯�� ����(�ݶ��̴� �簢�� ���θ� ä��� �귯���� ���� �귯��)
			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
			Rectangle(image->mHdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);
			SelectObject(hdc, oldBrush);
			///
			HBITMAP oldbitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
			DeleteObject(oldbitmap);
			#pragma endregion

			Resources::Insert(name + L"Image", image);

			return image;
		}
		Texture::Texture()
			:Resource(ugina::enums::eResourceType::Texture)
			,mbAlpha(false)
		{


		}

		Texture::~Texture()
		{
		}

		//�ؽ��ĸ� �ϴ� ������ �޸𸮿� �ø��� �Լ�(����� Resources Ŭ������ Load�Լ��� ���������)
		HRESULT Texture::Load(const std::wstring& path)
		{
			//aaaa.png�����̸� .���ĺ��� �������� ���ڿ��� ��ȯ (�� png(Ȯ����)�� ��ȯ)
			std::wstring ext = path.substr(path.find_last_of(L'.') + 1);
			
			if (ext == L"bmp")
			{
				mType = eTextureType::Bmp;
				//BMP���� �̹����� �ε��ؼ� HBITMAP�� ���ؼ� ����
				mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				
				//null�� ��ȯ�ϴ� ����
				if (mBitmap == nullptr)
				{
					return S_FALSE;
				}
				//��Ʈ�� ����ü�� ���ؼ� HBITMAP�� ������ ����
				BITMAP info = {};
			
				GetObject(mBitmap, sizeof(BITMAP), &info);
				
				mWidth = info.bmWidth;
				mHeight = info.bmHeight;

				//���� �̹����� 32��Ʈ ��Ʈ��(���İ��� �ִ� ��Ʈ���ΰ�)
				if (info.bmBitsPixel == 32)
				{
					mbAlpha = true;
				}
				//���� �̹����� 24��Ʈ ��Ʈ��(���İ��� ���� ��Ʈ���ΰ�)
				else if (info.bmBitsPixel == 24)
				{
					mbAlpha = false;
				}

				//���� ���ӿ� ���ǰ� �ִ� ����dc�� �����´�
				HDC maicDc = api.GetHdc();
				//��Ʈ���� �׸� DC(mhdc)�� ����DC�� ȣȯ�Ǵ� DC�� �����.
				mHdc = CreateCompatibleDC(maicDc);
				
				//�� ��Ʈ���� �׸� dc�� ��Ʈ���� �̹����� ������ ��Ʈ������ �ٲ۴�.
				HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
				DeleteObject(oldBitmap);
				
					
			}
			else if (ext == L"png")
			{
				mType = eTextureType::Png;
				mImage = Gdiplus::Image::FromFile(path.c_str());
				if (mImage == nullptr)
				{
					return S_FALSE;
				}
				mWidth=mImage->GetWidth();
				mHeight=mImage->GetHeight();
			}

			return S_OK;
		}
	}
}
