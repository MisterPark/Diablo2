#pragma once
#include "GameObject.h"
class BackGround :
    public GameObject
{
private:
    BackGround();
    virtual ~BackGround();

public:
    static BackGround* GetInstance();
    static void DestroyInstance();
    
    static void SetSprite(SpriteType _type);

    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

};

