// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#pragma comment(lib,"Msimg32.lib")

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <type_traits>
#include <direct.h>
#include <algorithm>

using namespace std;

// 사용자 추가
#include "Point.h"

#include "MemoryPool.h"
#include "Define.h"
#include "MainGame.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "TileManager.h"
#include "FileManager.h"

extern HWND g_hwnd;

#include "framework.h"

#include <io.h>

#pragma comment(lib, "fmodex_vc.lib")
#include "fmod.h"
#include "SoundMgr.h"

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#endif //PCH_H
