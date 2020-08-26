#pragma once
class Texture
{
public:
	Texture();
	~Texture();

	DWORD GetLastFrame();

	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	D3DXIMAGE_INFO imageInfo;
	DWORD rowCount = 1;
	DWORD colCount = 1;
};

