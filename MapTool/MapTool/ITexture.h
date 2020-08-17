#pragma once

struct TextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // 이미지 한장을 제어하기 위한 컴객체. 
	D3DXIMAGE_INFO imageInfo; //이미지의 정보를 담아둘 구조체. 
};

class ITexture abstract
{
public:
	explicit ITexture() = default;
	virtual ~ITexture() = default;

	virtual HRESULT InsertTexture(const wstring& filePath, const wstring& stateKey = L"", const DWORD& count = 0) = 0;
	virtual void ReleaseTexture() = 0;
	virtual const TextureInfo* GetTexture(const wstring& stateKey = L"", const DWORD& index = 0) = 0;
};

