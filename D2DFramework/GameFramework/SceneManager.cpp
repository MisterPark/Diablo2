#include "pch.h"
#include "SceneManager.h"

SceneManager* pSceneManager = nullptr;

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{
	if (pCurrentScene != nullptr)
	{
		pCurrentScene->OnUnloaded();
		delete pCurrentScene;
	}
	if (pReadyScene != nullptr)
	{
		delete pReadyScene;
	}
}

void SceneManager::LoadScene(IScene * pScene)
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		delete self.pReadyScene;
	}
	self.pReadyScene = pScene;
}

SceneManager* SceneManager::GetInstance()
{
	if (pSceneManager == nullptr)
	{
		pSceneManager = new SceneManager();
	}
	return pSceneManager;
}


void SceneManager::Release()
{
	delete pSceneManager;
}

void SceneManager::Update()
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		IScene* pReadyScene = self.pReadyScene;
		self.pReadyScene = nullptr;
		if (self.pCurrentScene != nullptr)
		{
			self.pCurrentScene->OnUnloaded();
			delete self.pCurrentScene;
		}
		self.pCurrentScene = pReadyScene;
		self.pCurrentScene->OnLoaded();
	}
	if (self.pCurrentScene)
	{
		self.pCurrentScene->Update();
	}
}

