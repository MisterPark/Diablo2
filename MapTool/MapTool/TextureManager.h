#pragma once

class ITexture;

enum class TextureType
{
	SINGLE,
	MULTI,
};

class TextureManager
{
private:
	TextureManager();
	~TextureManager();
public:
	static TextureManager* GetInstance();
	static void Release();

public:
};

