/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>

#include <game/server/OnTime/Shop/ShopItem/weapons.h>
#include "ShopCore.h"


CGui::CGui(CGameWorld *pGameWorld, int Owner)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Owner = Owner;
	m_Visible = false;
	m_Pos = vec2(0, 0);

	// ITEMS
	m_apShop[0] = new CAllWeapons(pGameWorld, m_Owner, m_Pos);
	
	m_apShop[0]->m_Visible = true;
	//m_Menu = 1;
	for(int i = 0; i < 24; i++)
	{
		if(i == 11 || i == 8)
			continue;

		//00m_apShop[i]->m_Visible = true;
	}

	GameWorld()->InsertEntity(this);
}

CGui::~CGui()
{
	for(int i = 0; i < 24; i++)
		delete m_apShop[i];
	//m_apShop = 0;

}
void CGui::Switch()
{
	for(int i = 0; i < 24; i++)
	{
		if(i == 11 || i == 8)
			continue;

		m_apShop[i]->m_Visible ^= true;
	}
}

void CGui::Reset()
{
	GS()->m_World.DestroyEntity(this);
	/*delete m_apShop;
	m_apShop[] = 0;*/
}

void CGui::Tick()
{
	CCharacter *pOwner = GS()->GetPlayerChar(m_Owner);

	if(!pOwner)
	{
		Reset();
		return;
	}

	if(GS()->Collision()->GetZoneValueAt(GS()->m_ZoneHandle_OnTime, pOwner->m_Pos) == ZONE_LSHOP && !pOwner->m_Menu)
	{
		dbg_msg("s","s");
		pOwner->m_Menu = 1;
	}
	else if(!GS()->Collision()->GetZoneValueAt(GS()->m_ZoneHandle_OnTime, pOwner->m_Pos) == ZONE_LSHOP && pOwner->m_Menu)
		pOwner->m_Menu = 0;

}

void CGui::CheckKlick(vec2 Pos)
{
	for(int i = 0; i < 24; i++)
	{
		if(length(m_apShop[i]->m_Pos-Pos) < 96)
			m_apShop[i]->m_Visible ^= true;
	}


}
void CGui::Menu()
{
	CCharacter *pOwner = GS()->GetPlayerChar(m_Owner);

	if(!pOwner)
		return;
	
	int Menu = pOwner->m_Menu;

	m_apShop[0]->m_Visible = false;
	for(int i = 0; i < 24; i++)
	{
		if((i == 11 || i == 8) && m_apShop[i])
			continue;

		//m_apShop[i]->m_Visible = false;
	}

	int Case = 0;
	int Start, End;

	if(Menu < 7 && Menu)
	{
		Start = (Menu-1)*3;
		End = 3*Menu;

		Case = 1;

		if(Menu == 3 || Menu == 4)
			Case = 2;
	}
	else if(Menu > 6 && Menu)
	{
		Start = 18;
		End = 24;
		Case = 3;
	}
	else
		return;
	

	for(int i = 0; i <= 0; i++)
	{
		if(i == 11 || i == 8)
			continue;

		m_apShop[i]->m_Visible = true;
		
		if(Case == 1)
			m_apShop[i]->m_Pos = pOwner->m_Pos + normalize(GetDir(pi/180 * 270-5+(i-Start)*5))*250;
		else if(Case == 2)
			m_apShop[i]->m_Pos = pOwner->m_Pos + normalize(GetDir(pi/180 * 270-1+(i-Start)*2))*250;
		else if(Case == 3)
			m_apShop[i]->m_Pos = pOwner->m_Pos + normalize(GetDir(pi/180 * 270-3*1+(i-Start)*1))*250;
	}

}

void CGui::Snap(int SnappingClient)
{
	if(SnappingClient != m_Owner)
		return;

	Menu();
	/*CCharacter *pOwner = GS()->GetPlayerChar(m_Owner);

	if(pOwner)
	{
		
		for(int i = 0; i < 24; i++)
		{
			if(i == 11 || i == 8)
				continue;

			m_apShop[i]->m_Pos = pOwner->m_Pos + normalize(GetDir(pi/180 * ((180 + i*(i?-1:1)*15)%360)))*250;
		}
	}*/




	
	
}
