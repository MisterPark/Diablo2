#pragma once
#include "Character.h"
class Monster :
    public Character
{
public:
    Monster() = default;
    virtual ~Monster() = default;

    virtual void Update() override;
    virtual void Render() override;
    virtual void OnCollision(GameObject* _other);

    virtual void Die() override;

    
    void SetSpawnPosition(int x, int y);
    void SetBackAndForth(int x, int y);

    bool IsTargetClose();

    // ÆÐÅÏ
    void MoveLeft(); // ¿ÞÂÊÀ¸·Î Âß
    void BackAndForth(); // ¿Ô´Ù¸®°¬´Ù¸®


public:
    Transform spawnPos{ 0.f,0.f };
    Transform backAndForthPos{ 0.f,0.f };
    float attackRange = 100.f;
    bool backAndForthFlag = false;

};

