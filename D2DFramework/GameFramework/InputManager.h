#pragma once

#define RANGE_OF_KEYS 256

class InputManager
{
private:
	InputManager();
	~InputManager();

public:
	static InputManager* GetInstance();
	static void Update();
	static void Release();
	static void Clear();
	// Ű ������
	static bool GetKey(int _vkey);
	// Ű �ٿ�
	static bool GetKeyDown(int _vkey);
	// Ű ��
	static bool GetKeyUp(int _vkey);
	// ���콺 Ÿ�� ��ġ
	static bool GetTileIndex(POINT* _outPoint);


private:
	bool keys[RANGE_OF_KEYS] = {};
	bool keyDowns[RANGE_OF_KEYS] = {};
	bool keyUps[RANGE_OF_KEYS] = {};
};

