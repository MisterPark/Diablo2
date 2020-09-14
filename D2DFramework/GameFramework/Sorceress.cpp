#include "pch.h"
#include "Sorceress.h"

Sorceress::Sorceress()
{
	anim->SetSpriteKey(SpriteType::SO_NU_HTH);
	anim->SetLoop(true);
	anim->SetDelay(0.08f);

	sprites[(int)CharacterState::NU] = SpriteType::SO_NU_HTH;
	sprites[(int)CharacterState::RN] = SpriteType::SO_RN_HTH;

	//sprites[(int)CharacterState::NU_STF] = SpriteType::SO_NU_STF;
	sprites[(int)CharacterState::TN_STF] = SpriteType::SO_TN_STF;
	sprites[(int)CharacterState::RN_STF] = SpriteType::SO_RN_STF;
	sprites[(int)CharacterState::A1_STF] = SpriteType::SO_A1_STF;
	sprites[(int)CharacterState::A2_STF] = SpriteType::SO_A2_STF;
	sprites[(int)CharacterState::SC_STF] = SpriteType::SO_SC_STF;
	sprites[(int)CharacterState::GH_STF] = SpriteType::SO_GH_STF;

    // stat
	nick = L"닉네임";
    className = L"소서리스";


	stat[(int)StatType::LIFE] = stat[(int)StatType::MAX_LIFE];
	stat[(int)StatType::MANA] = stat[(int)StatType::MAX_MANA];
}

Sorceress::~Sorceress()
{
}

void Sorceress::Update()
{
	Character::Update();
}

void Sorceress::Render()
{
	Character::Render();
}
