#include "pch.h"
#include "Sorceress.h"

Sorceress::Sorceress()
{
	anim->SetSpriteKey(SpriteType::SO_NU_HTH);
	anim->SetLoop(true);
	anim->SetDelay(0.08f);

	sprites[(int)CharacterState::NU] = SpriteType::SO_NU_HTH;
	sprites[(int)CharacterState::RN] = SpriteType::SO_RN_HTH;

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
