#pragma once
#include "IScene.h"
class TitleScene :
    public IScene
{
    // IScene��(��) ���� ��ӵ�
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    static void LoadSingleGameScene();
};

