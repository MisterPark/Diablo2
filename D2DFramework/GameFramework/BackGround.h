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

    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;

};

