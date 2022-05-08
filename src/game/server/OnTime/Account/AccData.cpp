/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <string.h>
#include <fstream>
#include <engine/config.h>
#include <engine/shared/config.h>
#include "AccData.h"
#include <engine/server/crypt.h>

#include <teeuniverses/components/localization.h>

CAccount::CAccount(CPlayer *pPlayer, CGS *pGameServer)
{
	m_pPlayer = pPlayer;
	m_pGameServer = pGameServer;
}

void CAccount::Login(char *Username, char *Password, int ClientID)
{
	char aBuf[125];
	if (m_pPlayer->m_AccData.m_UserID)
		return GS()->SendChatTarget(m_pPlayer->GetCID(), _("Already logged in"));

	char aHash[64]; //Result
	mem_zero(aHash, sizeof(aHash));
	Crypt(Password, (const unsigned char*) "d9", 1, 14, aHash);

	GS()->Login(Username, aHash, m_pPlayer->GetCID());
}

void CAccount::Register(char *Username, char *Password, int ClientID)
{
	char aBuf[125];
	if(m_pPlayer->m_AccData.m_UserID)
		return GS()->SendChatTarget(m_pPlayer->GetCID(), _("Already logged in"));

	GS()->Register(Username, Password, m_pPlayer->GetCID());
}

bool CAccount::Exists(const char *Username)
{
}

bool CAccount::Apply()
{
	return GS()->Apply(
        m_pPlayer->m_AccData.m_Username, 
        m_pPlayer->m_AccData.m_Password, 
        m_pPlayer->GetCID(), 
        m_pPlayer->GetLanguage(), 
        m_pPlayer->m_AccData.m_UserID, 
        m_pPlayer->m_AccData.m_Level, 
        m_pPlayer->m_AccData.m_Exp, 
        m_pPlayer->m_AccData.m_Lifes);
}

void CAccount::Reset()
{
	m_pPlayer->m_AccData.m_UserID = 0;
	str_copy(m_pPlayer->m_AccData.m_Username, "", 32);
	str_copy(m_pPlayer->m_AccData.m_Password, "", 32);
	
	m_pPlayer->m_AccData.m_Exp = m_pPlayer->m_AccData.m_Level = m_pPlayer->m_AccData.m_Lifes = 0;
    m_pPlayer->m_AccData.m_Weapons = 0;
}

void CAccount::NewPassword(char *NewPassword)
{
	char aHash[64];
	Crypt(NewPassword, (const unsigned char*) "d9", 1, 14, aHash);
	
	str_copy(m_pPlayer->m_AccData.m_Password, NewPassword, 32);
	Apply();
	
	dbg_msg("account", "Password changed - ('%s')", m_pPlayer->m_AccData.m_Username);
	GS()->SendChatTarget(m_pPlayer->GetCID(), _("Password successfully changed!"));
}