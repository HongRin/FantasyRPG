#include "PlayerInfo.h"

FPlayerInfo::FPlayerInfo()
{
	Atk = 200.0f;
	Hp = MaxHp = 999.0f;
	Def = 30.0f;
	Mp = MaxMp = 200.0f;
	StatPoint = 50;
	InventorySlotConut = 20;
	Money = 10000;
}

void FPlayerInfo::Initialize()
{
	WalkSpeed = 250;

	RunSpeed = 750;
}
