#pragma once

class Texture;

enum class SpriteType
{
	NONE,
	ACT1_TOWN_FLOOR,
	ACT1_OUTDOOR_FLOOR,
	ACT1_TOWN_FENCE,

	BG_BLACK,
	BG_INTRO,
	BG_TITLE,
	BG_CHAR_CREATION,

	UI_CURSOR,
	UI_LOGO,
	UI_BTN_WIDE,
	UI_BTN_MEDIUM,
	UI_BTN_HALFWIDE,
	UI_BTN_NARROW,
	UI_BTN_BUYSELL,
	UI_TAB_BUYSELL,
	UI_TEXTBOX,
	UI_PANEL_800L,
	UI_PANEL_800R,
	UI_PANEL_STATUS,
	UI_PANEL_INVEN,
	UI_PANEL_BUYSELL,
	UI_PANEL_STATUS_BAR,
	UI_HP_BALL,
	UI_MP_BALL,
	UI_RECT_RED,
	UI_RECT_BLACK_ALPHA,

	ITEM_INV_SST,
	ITEM_FLP_SST,
	ITEM_INV_CAP,
	ITEM_FLP_CAP,
	ITEM_INV_QLT,
	ITEM_FLP_QLT,
	ITEM_INV_LBL,
	ITEM_FLP_LBL,
	ITEM_INV_LBT,
	ITEM_FLP_LBT,

	EFFECT_FIRECAST,
	EFFECT_COLDCAST,
	EFFECT_LIGHTCAST,
	EFFECT_EXPLODE,
	EFFECT_METEOR_TARGET,

	SKILL_FIREBOLT,
	SKILL_FIREBALL,
	SKILL_INFERNO,
	SKILL_FIREWALL_S,
	SKILL_FIREWALL,
	SKILL_FIREWALL_E,
	SKILL_SMALLFIRE_S,
	SKILL_SMALLFIRE,
	SKILL_SMALLFIRE_E,
	SKILL_METEOR,
	SKILL_HYDRA,

	SKILL_TELEPORT,
	


	SO_BW,
	SO_NU_HTH,
	SO_RN_HTH,
	
	SO_TN_STF,
	SO_RN_STF,
	SO_A1_STF,
	SO_A2_STF,
	SO_SC_STF,
	SO_GH_STF,
};

class D2DRenderManager
{
private:
	D2DRenderManager();
	~D2DRenderManager();

public:
	static D2DRenderManager* GetInstance();
	static void DestroyInstance();

	static HRESULT Initialize();
	static void Release();

	static void Clear();
	static void Present(HWND renderTarget = nullptr);

	static LPDIRECT3DDEVICE9 GetDevice();
	static LPD3DXSPRITE GetSprite();
	static Texture* GetTexture(SpriteType _key);
	static LPD3DXLINE GetLine();

	static HRESULT LoadSprite(const wstring& filePath, SpriteType spriteKey, DWORD row, DWORD col);
	static void DrawSprite(SpriteType spriteKey, Transform transform, int index);
	static void DrawUI(SpriteType spriteKey, Transform transform, int index);
	static void DrawUI(SpriteType spriteKey, Vector3 pos, int index);
	static void DrawCharacter(SpriteType spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);
	static void DrawTile(SpriteType spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);
	static void DrawSubTile(SpriteType spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);
	static void DrawItem(SpriteType spriteKey, Vector3 pos, int index);

	static void DrawImage(SpriteType spriteKey, Transform transform);
	static void DrawImage(SpriteType spriteKey, float x, float y, float verticalPer);

	static void DrawString(const string& text);
	static void DrawString(const wstring& text);
	static void DrawString(const wstring& text, float x, float y, D3DXCOLOR color);
	static void DrawString(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);
	static void DrawString(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color);
	static void DrawString(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect);

	static void DrawLine(float sx, float sy, float ex, float ey);
	static void DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color);

	static void DrawRect(float sx, float sy, float ex, float ey);
	static void DrawRectWorld(float sx, float sy, float ex, float ey);


private:
	// 실질적으로 장치를 다룰 객체. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPDIRECT3D9 pSDK = nullptr;
	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;
	LPD3DXLINE pLine = nullptr;

	map<SpriteType, Texture*> textureMap;
};

