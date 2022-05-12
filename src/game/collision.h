/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <base/vmath.h>

class CCollision
{
	class CTile *m_pTiles;
	int m_Width;
	int m_Height;
	class CLayers *m_pLayers;

	bool IsTileSolid(int x, int y);

public:
	enum
	{
		COLFLAG_SOLID=1,
		COLFLAG_DEATH=2,
		COLFLAG_NOHOOK=4,
		COLFLAG_C1=8,
		COLFLAG_C2=16,
		COLFLAG_C3=32,
		COLFLAG_C4=64,
		COLFLAG_C5=128,
		COLFLAG_C6=256,
		COLFLAG_C7=512,
		COLFLAG_C8=1024,
		COLFLAG_C9=2048,
	};

	CCollision();
	void Init(class CLayers *pLayers);
	bool CheckPoint(float x, float y) { return IsTileSolid(round_to_int(x), round_to_int(y)); }
	bool CheckPoint(vec2 Pos) { return CheckPoint(Pos.x, Pos.y); }
	int GetCollisionAt(float x, float y) { return GetTile(round_to_int(x), round_to_int(y)); }
	int GetWidth() { return m_Width; };
	int GetHeight() { return m_Height; };
	int IntersectLine(vec2 Pos0, vec2 Pos1, vec2 *pOutCollision, vec2 *pOutBeforeCollision);
	void MovePoint(vec2 *pInoutPos, vec2 *pInoutVel, float Elasticity, int *pBounces);
	void MoveBox(vec2 *pInoutPos, vec2 *pInoutVel, vec2 Size, float Elasticity);
	bool TestBox(vec2 Pos, vec2 Size);

	int GetTile(int x, int y);
	int GetTile(vec2 Pos) { return GetTile(Pos.x, Pos.y); }

	int GetMapIndex(vec2 Pos) const;
	int GetTileIndex(int Index);
	int GetPureMapIndex(vec2 Pos)
	{
		int Nx = clamp((int)Pos.x/32, 0, m_Width-1);
		int Ny = clamp((int)Pos.y/32, 0, m_Height-1);
		return Ny*m_Width+Nx;
	}
};

#endif
