#include "pch.h"
#include "TestScene.h"

void TestScene::OnLoaded()
{
	ObjectManager::CreateObject(ObjectType::CHARACTER);
}

void TestScene::OnUnloaded()
{
}

void TestScene::Update()
{
}
