#include "pch.h"
#include "SingleTexture.h"

SingleTexture::SingleTexture()
{
}

SingleTexture::~SingleTexture()
{
    ReleaseTexture();
}

HRESULT SingleTexture::InsertTexture(const wstring& filePath, const wstring& stateKey, const DWORD& count)
{
	pInfo = new TextureInfo;
	ZeroMemory(pInfo, sizeof(TextureInfo));

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &pInfo->imageInfo)))
	{
		AfxMessageBox(L"이미지 정보 불러오기 실패");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		GraphicDevice::GetDevice(),
		filePath.c_str(),
		pInfo->imageInfo.Width,
		pInfo->imageInfo.Height,
		pInfo->imageInfo.MipLevels,
		0,
		pInfo->imageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&pInfo->pTexture)))
	{
		wstring wstrErrMessage = filePath + L"Create Texture Failed";
		AfxMessageBox(wstrErrMessage.c_str());
		return E_FAIL;
	}
	return S_OK;
}

void SingleTexture::ReleaseTexture()
{
	if (pInfo)
	{
		delete pInfo;
		pInfo = nullptr;
	}
}

const TextureInfo* SingleTexture::GetTexture(const wstring& stateKey, const DWORD& index)
{
	return pInfo;
}
