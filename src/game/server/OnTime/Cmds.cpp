#include <stdio.h>
#include <string.h>

#include <engine/shared/config.h>
#include <engine/server.h>
#include <game/version.h>
#include "Cmds.h"
#include "Account/AccData.h"

#include <teeuniverses/components/localization.h>
CCmd::CCmd(CPlayer *pPlayer, CGS *pGameServer)
{
	m_pPlayer = pPlayer;
	m_pGameServer = pGameServer;
}

bool CCmd::ChatCmd(CNetMsg_Cl_Say *Msg)
{
    if(!strncmp(Msg->m_pMessage, "/login", 6))
	{
		LastChat();		
		char Username[256], Password[256];
		if(sscanf(Msg->m_pMessage, "/login %s %s", Username, Password) != 2) 
		{
            GameServer()->SendChatTarget(m_pPlayer->GetCID(), _("Use: /login <username> <password>"));
            return true;
        }

		if(str_length(Username) > 15 || str_length(Username) < 4 || str_length(Password) > 15 || str_length(Password) < 4) 
        {
            GameServer()->SendChatTarget(m_pPlayer->GetCID(), _("Username / Password must contain 4-15 characters"));
            return true;
        }
		m_pPlayer->m_pAccount->Login(Username, Password, m_pPlayer->GetCID());
		return true;
	}
	else if(!strncmp(Msg->m_pMessage, "/register", 9))
	{
		LastChat();
		
		char Username[256], Password[256];
		if(sscanf(Msg->m_pMessage, "/register %s %s", Username, Password) != 2) 
		{	
            GameServer()->SendChatTarget(m_pPlayer->GetCID(), _("Use /register <username> <password>'"));
            return true;
        }
		if(str_length(Username) > 15 || str_length(Username) < 4 || str_length(Password) > 15 || str_length(Password) < 4)
		{
            GameServer()->SendChatTarget(m_pPlayer->GetCID(), _("Username and Password must contain 4-15 characters"));
            return true;
        }
        else if (!strcmp(Username, Password))
		{	
            GameServer()->SendChatTarget(m_pPlayer->GetCID(), _("Username and Password must be different"));
            return true;
        }
		m_pPlayer->m_pAccount->Register(Username, Password, m_pPlayer->GetCID());
		return true;
	}

    return false;
}

void CCmd::LastChat()
{
	 m_pPlayer->m_LastChat = GameServer()->Server()->Tick();
}
