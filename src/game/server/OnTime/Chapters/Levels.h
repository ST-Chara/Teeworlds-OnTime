#ifndef CHAPTER_LEVELS_H
#define CHAPTER_LEVELS_H

#include <game/server/gamemodes/mod.h>
#include <game/server/gamecontext.h>

enum Chapters
{
    Chapter1=0,
    Chapter2,
    Chapter3,
    Chapter4,
    Chapter5,
    Chapter6,
    Chapter7,
    Chapter8,
    Chapter9,
};

enum Levels
{
    // Chapter 1.
    Chapter1_Level1_BlackHole,
    Chapter1_Level2_BlackCity,
    Chapter1_Level3_BlackLeader,
    Chapter1_Level4_Road,
    Chapter1_Boss1_TimeGallery,

    // Chapter 2.
    Chapter2_Level5_BloodTown,
};

enum LevelType
{
    LevelTYPE_FreeGo,
    LevelTYPE_Keep,
    LevelTYPE_Boss,
};

class CGameControllerMOD;

class CLevel
{
    CGS *m_pGameServer;
	IServer *m_pServer;
	CGameControllerMOD* m_pController;

public:
    CLevel(CGS* pGameServer, CGameControllerMOD* pController)
	{
		m_pGameServer = pGameServer;
		m_pServer = m_pGameServer->Server();
		m_pController = pController;
	}
	
    const char *m_LevelName;
    int m_TypeLevel;
    int m_Chapter;
protected:
	CGameControllerMOD *Controller() const { return m_pController; }
	CGS *GameServer() const { return m_pGameServer; }
	IServer *Server() const { return m_pServer; }
};
#endif