/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "mod.h"
#include <game/server/entities/character.h>
#include <game/server/player.h>
#include <game/server/gamecontext.h>

#include <game/server/OnTime/Chapters/Chapter1/Level1_BlackHole.h>

CGameControllerMOD::CGameControllerMOD(class CGS *pGS)
: IGameController(pGS)
{
	// Exchange this to a string that identifies your game mode.
	// DM, TDM and CTF are reserved for teeworlds original modes.
	if(rand()%2 == 1)
		m_pGameType = "OnTime";
	else
		m_pGameType = "OffTime";
}

void CGameControllerMOD::Tick()
{
	// this is the main part of the gamemode, this function is run every tick

	IGameController::Tick();
}
