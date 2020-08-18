#include "pch.h"
#include "MultiTexture.h"

MultiTexture::MultiTexture()
{
}

MultiTexture::~MultiTexture()
{
    ReleaseTexture();
}

HRESULT MultiTexture::InsertTexture(const wstring& filePath, const wstring& stateKey, const DWORD& count)
{
	auto& iter_find = multiTextureMap.find(stateKey);
	TCHAR szFilePath[MAX_PATH] = L"";
	if (multiTextureMap.end() == iter_find)
	{
		for (DWORD i = 0; i < count; ++i)
		{
			wsprintf(szFilePath, filePath.c_str(), i);
			TextureInfo* pTexInfo = new TextureInfo;
			ZeroMemory(pTexInfo, sizeof(TextureInfo));

			if (FAILED(D3DXGetImageInfoFromFile(szFilePath, &pTexInfo->imageInfo)))
			{
				AfxMessageBox(L"이미지 정보 불러오기 실패");
				if (pTexInfo)
				{
					delete pTexInfo;
					pTexInfo = nullptr;
				}
				return E_FAIL;
			}

			if (FAILED(D3DXCreateTextureFromFileEx(
				GraphicDevice::GetDevice(),
				szFilePath,
				pTexInfo->imageInfo.Width,
				pTexInfo->imageInfo.Height,
				pTexInfo->imageInfo.MipLevels,
				0,
				pTexInfo->imageInfo.Format,
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				nullptr,
				nullptr,
				&pTexInfo->pTexture)))
			{
				wstring wstrErrMessage = filePath + L"Create Texture Failed";
				AfxMessageBox(wstrErrMessage.c_str());
				if (pTexInfo)
				{
					delete pTexInfo;
					pTexInfo = nullptr;
				}
				return E_FAIL;
			}
			multiTextureMap[stateKey].emplace_back(pTexInfo);
		}
	}
	return S_OK;
}

void MultiTexture::ReleaseTexture()
{
	for (auto& rPair : multiTextureMap)
	{
		for (auto& pTexInfo : rPair.second)
		{
			if (pTexInfo)
			{
				delete pTexInfo;
				pTexInfo = nullptr;
			}
		}
		rPair.second.clear();
		rPair.second.swap(vector<TextureInfo*>()); // 택 1 
		//rPair.second.shrink_to_fit(); 
	}
}

const TextureInfo* MultiTexture::GetTexture(const wstring& stateKey, const DWORD& index)
{
	auto& iter_Find = multiTextureMap.find(stateKey);
	if (iter_Find == multiTextureMap.end())
		return nullptr;

	return iter_Find->second[index];
}
