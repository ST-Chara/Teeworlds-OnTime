/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_MOD_H
#define GAME_SERVER_GAMEMODES_MOD_H
#include <game/server/gamecontroller.h>

class CLevel;
#include <game/server/OnTime/Chapters/Levels.h>
#include <map>
#include <vector>

// you can subclass GAMECONTROLLER_CTF, GAMECONTROLLER_TDM etc if you want
// todo a modification with their base as well.
class CGameControllerMOD : public IGameController
{
public:
	CGameControllerMOD(class CGS *pGS);
	virtual void Tick();
	// add more virtual functions here if you wish
private:
	std::vector<CLevel*> m_Levels;
};
#endif
