#ifndef GAME_SERVER_CMD_H
#define GAME_SERVER_CMD_H
#include "game/server/gamecontext.h"

class CCmd
{
public:
	CCmd(CPlayer *pPlayer, CGS *pGameServer);
	bool ChatCmd(CNetMsg_Cl_Say *Msg);

private:
	CPlayer *m_pPlayer;
	CGS *m_pGameServer;
	CGS *GS() const { return m_pGameServer; }

	void LastChat();
};

#endif