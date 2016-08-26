#pragma once

#include "MovementExport.h"
#include "Projectile.h"
using namespace PROJECTILE;
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
#include "MapLoad.h"
using namespace MAPLOADER;

namespace MOVEMENT
{
	class MOVEMENT_API CMovement
	{
	public:
		CMovement();
		~CMovement();

		void ProjectileUpdate(const float timeDiff, double dt, int scale, PROJECTILE::Projectile::ProjType type);

		PROJECTILE::Projectile* Projectile;
		PROJECTILE::Projectile* FetchProjectile();
		std::vector<PROJECTILE::Projectile *>m_projectileList;

		enum GEOMETRY_TYPE
		{
			GEO_TILEHERO_FRAME0,
			GEO_TILEHERO_FRAME1,
			GEO_TILEHERO_FRAME2,
			GEO_TILEHERO_FRAME3,
			NUM_GEOMETRY,
		};

		void Init(void);
		bool isOnGround(void);
		bool isJumpUpwards(void);
		bool isFreeFall(void);
		void SetOnFreeFall(bool isOnFreeFall);
		void SetToJumpUpwards(bool isOnJumpUpwards);
		void SetToStop(void);
		void SetPos_x(int pos_x);
		void SetPos_y(int pos_y);
		void SetJumpspeed(int jumpspeed);

		void MoveUpDown(const bool mode, const float timeDiff);
		void MoveLeftRight(const bool mode, const float timeDiff);

		int GetPos_x(void);
		int GetPos_y(void);
		int GetJumpspeed(void);
		int GetMapOffset_x(void);
		int GetMapOffset_y(void);
		int GetMapFineOffset_x(void);
		int GetMapFineOffset_y(void);

		void UpdateJumpUpwards();
		void UpdateFreeFall();
		void HeroUpdate(MapLoad* m_cMap);

		void SetAnimationInvert(bool heroAnimationInvert);
		bool GetAnimationInvert(void);
		void SetAnimationCounter(int heroAnimationCounter);
		int GetAnimationCounter(void);

		void ConstrainHero(const int leftBorder, const int rightBorder,
			const int topBorder, const int bottomBorder,
			float timeDiff);

		bool walking;
		bool facingRight;

		bool TransitLevel;

	private:
		Vector2 theHeroPosition;
		int jumpspeed;
		bool hero_inMidAir_Up;
		bool hero_inMidAir_Down;
		bool heroAnimationInvert;
		int heroAnimationCounter;

		// For scrolling.
		int mapOffset_x, mapOffset_y;
		int mapFineOffset_x, mapFineOffset_y;

	};

}


