#pragma once
#include "uginaResource.h"

namespace ugina
{
	namespace graphics
	{	
		class Texture : public Resource
		{
		public:
			enum class eTextureType
			{
				Bmp,
				Png,
				None,
				Count
			};
			Texture();
			~Texture();

			virtual HRESULT Load(const std::wstring& path) override;

			UINT GetWidth() { return mWidth; }
			UINT GetHeight() { return mHeight; }
			HDC GetHdc() { return mHdc; }
			eTextureType GetTextureType() { return mType; }
			Gdiplus::Image* getImage() { return mImage; }
		private:
			eTextureType mType;
			Gdiplus::Image* mImage;
			HBITMAP mBitmap;
			HDC mHdc;

			UINT mWidth;
			UINT mHeight;
		};
	}
}

