#pragma once
#include "ITexture.h"
class SingleTexture : public ITexture
{
public:
	explicit SingleTexture();
	virtual ~SingleTexture();

	// ITexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring& filePath, const wstring& stateKey = L"", const DWORD& count = 0) override;
	virtual void ReleaseTexture() override;
	virtual const TextureInfo* GetTexture(const wstring& stateKey = L"", const DWORD& index = 0) override;

private:
	TextureInfo* pInfo = nullptr;
};

