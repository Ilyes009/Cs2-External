#pragma once
#include "../../Source/Memory/Memory.hpp"
#include "../../Source/Globals/Globals.hpp"
#include "../Readers/Game.hpp"
#include "../Readers/LocalPlayer.hpp"



VOID ANTIFLASH()
{
	if (game.FlashDuration > 0)
	{
		mem.WriteMemory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime, 0);
	}
}