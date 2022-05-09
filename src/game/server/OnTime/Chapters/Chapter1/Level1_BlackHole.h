#ifndef CHAPTER1_LEVEL1
#define CHAPTER1_LEVEL1

#include "../Levels.h"

class Level1 : public CLevel
{
public:
    Level1(CGS* pGameServer, CGameControllerMOD* pController);
    ~Level1() {}

    void Tick();
	int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
};

#endif