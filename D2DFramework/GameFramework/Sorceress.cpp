#include "pch.h"
#include "Sorceress.h"

Sorceress::Sorceress()
{
	//anim->SetSpriteKey(SpriteType::SO_NU_HTH);
	//anim->SetLoop(true);
	//anim->SetDelay(0.08f);

	// sprite
	anims[(int)CharacterState::NU].SetSpriteKey(SpriteType::SO_NU_HTH);
	anims[(int)CharacterState::NU].SetLoop(true);
	anims[(int)CharacterState::NU].SetDelay(0.08f);
	anims[(int)CharacterState::TN].SetSpriteKey(SpriteType::SO_NU_HTH);
	anims[(int)CharacterState::TN].SetLoop(true);
	anims[(int)CharacterState::TN].SetDelay(0.08f);
	anims[(int)CharacterState::RN].SetSpriteKey(SpriteType::SO_RN_HTH);
	anims[(int)CharacterState::RN].SetLoop(true);
	anims[(int)CharacterState::RN].SetDelay(0.08f);

	//sprites[(int)CharacterState::NU_STF] = SpriteType::SO_NU_STF;
	anims[(int)CharacterState::TN_STF].SetSpriteKey(SpriteType::SO_TN_STF);
	anims[(int)CharacterState::RN_STF].SetSpriteKey(SpriteType::SO_RN_STF);
	anims[(int)CharacterState::A1_STF].SetSpriteKey(SpriteType::SO_A1_STF);
	anims[(int)CharacterState::A2_STF].SetSpriteKey(SpriteType::SO_A2_STF);
	anims[(int)CharacterState::SC_STF].SetSpriteKey(SpriteType::SO_SC_STF);
	anims[(int)CharacterState::GH_STF].SetSpriteKey(SpriteType::SO_GH_STF);

	anims[(int)CharacterState::TN_STF].SetLoop(true);
	anims[(int)CharacterState::RN_STF].SetLoop(true);
	anims[(int)CharacterState::A1_STF].SetLoop(false);
	anims[(int)CharacterState::A2_STF].SetLoop(false);
	anims[(int)CharacterState::SC_STF].SetLoop(false);
	anims[(int)CharacterState::GH_STF].SetLoop(false);

	anims[(int)CharacterState::TN_STF].SetDelay(0.05f);
	anims[(int)CharacterState::RN_STF].SetDelay(0.05f);
	anims[(int)CharacterState::A1_STF].SetDelay(0.05f);
	anims[(int)CharacterState::A2_STF].SetDelay(0.05f);
	anims[(int)CharacterState::SC_STF].SetDelay(0.05f);
	anims[(int)CharacterState::GH_STF].SetDelay(0.05f);

    // stat
	nick = L"닉네임";
    className = L"소서리스";


	stat[(int)StatType::LIFE] = stat[(int)StatType::MAX_LIFE] = 100;
	stat[(int)StatType::MANA] = stat[(int)StatType::MAX_MANA] = 100;
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
