#include "pch.h"
#include "InputManager.h"

InputManager* pInputManager = nullptr;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance()
{
	if (pInputManager == nullptr)
	{
		pInputManager = new InputManager();
	}

	return pInputManager;
}

void InputManager::Update()
{
	Clear();

	for (int i = 0; i < RANGE_OF_KEYS; i++)
	{
		SHORT keystate = GetAsyncKeyState(i);
		pInputManager->keys[i] = keystate & 0x8001;
		pInputManager->keyDowns[i] = keystate & 0x0001;
		pInputManager->keyUps[i] = keystate & 0x8000;
	}
	
}

void InputManager::Initialize()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

}

void InputManager::Release()
{
	delete pInputManager;
	pInputManager = nullptr;
}

void InputManager::Clear()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

	ClearMouseState();
}

void InputManager::ClearMouseState()
{
	int count = MaxOfEnum<Keys>();
	for (int i = 2; i < count; i++)
	{
		if (pInputManager->mouse[i])
		{
			pInputManager->mouseFrameCount[i]++;
			if (pInputManager->mouseFrameCount[i] == dfINPUT_LIFE_FRAME)
			{
				pInputManager->mouseFrameCount[i] = 0;
				pInputManager->mouse[i] = false;
			}
		}
	}
		

}

bool InputManager::GetKey(int _vkey)
{
	return pInputManager->keys[_vkey];
}

bool InputManager::GetKeyDown(int _vkey)
{
	return pInputManager->keyDowns[_vkey];
}

bool InputManager::GetKeyUp(int _vkey)
{
	return pInputManager->keyUps[_vkey];
}

bool InputManager::GetMouseLButton()
{
	return pInputManager->mouse[(int)Keys::LBUTTON];
}

bool InputManager::GetMouseLButtonUp()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_UP];
}

bool InputManager::GetMouseLButtonDown()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOWN];
}

bool InputManager::GetMouseLButtonDouble()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOUBLE];
}

bool InputManager::GetMouseRButton()
{
	return pInputManager->mouse[(int)Keys::RBUTTON];
}

bool InputManager::GetMouseRButtonUp()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_UP];
}

bool InputManager::GetMouseRButtonDown()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOWN];
}

bool InputManager::GetMouseRButtonDouble()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOUBLE];
}

bool InputManager::GetTileIndex(POINT * _outPoint)
{
	if (_outPoint == nullptr) return false;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	POINT idx;
	idx.x = (pt.x + Camera::GetX()) / dfTILE_W;
	idx.y = (pt.y + Camera::GetY()) / dfTILE_H;

	*_outPoint = idx;

	return true;
}

POINT InputManager::GetMousePosOnClient()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	return pt;
}

POINT InputManager::GetMousePosOnWorld()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	pt.x += Camera::GetX();
	pt.y += Camera::GetY();

	return pt;
}
