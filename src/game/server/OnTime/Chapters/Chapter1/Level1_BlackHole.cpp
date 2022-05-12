#include <engine/shared/config.h>
#include "Level1_BlackHole.h"

Level1::Level1(CGS* pGS, CGameControllerMOD* pController) : CLevel(pGS, pController)
{
	m_LevelName = "blackhole";
	m_TypeLevel = LevelTYPE_FreeGo;
    m_Chapter = 1;
}