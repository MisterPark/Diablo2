#pragma once
#include "ITexture.h"
class MultiTexture : public ITexture
{
public:
	explicit MultiTexture();
	virtual ~MultiTexture();

	// ITexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring& filePath, const wstring& stateKey = L"", const DWORD& count = 0) override;
	virtual void ReleaseTexture() override;
	virtual const TextureInfo* GetTexture(const wstring& stateKey = L"", const DWORD& index = 0) override;

private:
	map<wstring, vector<TextureInfo*>> multiTextureMap;
};

