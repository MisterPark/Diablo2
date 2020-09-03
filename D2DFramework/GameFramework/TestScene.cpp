#include "pch.h"
#include "TestScene.h"

void TestScene::OnLoaded()
{

	TileManager::Load("Act1Tile1.dat");

	ObjectManager::CreateObject(ObjectType::CHARACTER);
}

void TestScene::OnUnloaded()
{
}

void TestScene::Update()
{
}
