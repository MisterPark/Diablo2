#pragma once

#define dfCLIENT_WIDTH 800
#define dfCLIENT_HEIGHT 600
#define dfFPS 60
#define dfPI 3.141592f
#define dfGRAVITY 9.8f
#define dfJUMP_COUNT 10

template<typename EnumT>
constexpr int MaxOfEnum()
{
	return (int)EnumT::END;
}

enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,

	END
};

enum class StatType
{
	LEVEL,
	EXP,
	MAX_EXP,
	STRENGTH,
	DEXTERITY,
	VITALITY,
	ENERGY,
	STAT_POINT,
	STEMINA,
	MAX_STEMINA,
	LIFE,
	MAX_LIFE,
	MANA,
	MAX_MANA,
	FIRE_RES,
	COLD_RES,
	LIGHT_RES,
	POISON_RES,

	END
};