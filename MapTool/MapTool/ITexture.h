#pragma once

struct TextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // �̹��� ������ �����ϱ� ���� �İ�ü. 
	D3DXIMAGE_INFO imageInfo; //�̹����� ������ ��Ƶ� ����ü. 
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

