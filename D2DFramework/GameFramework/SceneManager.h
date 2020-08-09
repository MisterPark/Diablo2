#pragma once

#include "IScene.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();
	static void LoadScene(IScene * pScene);
public:
	static SceneManager* GetInstance();
	static void Release();
	static void Update();
	//�Ű� ���ڰ� ���� �� ������ ȣ��
	template<typename SceneT>
	static void LoadScene();
	template<typename SceneT, typename ...ArgT>
	static void LoadScene(ArgT&& ...args);
	
	IScene* pCurrentScene = nullptr;
	IScene* pReadyScene = nullptr;
};

template<typename SceneT>
inline void SceneManager::LoadScene()
{
	LoadScene(static_cast<IScene*>(new SceneT{}));
}

template<typename SceneT, typename ...ArgT>
inline void SceneManager::LoadScene(ArgT&& ...args)
{
	LoadScene(static_cast<IScene*>(new SceneT{std::forward<ArgT>(args) ... }));
}
